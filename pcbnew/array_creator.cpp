/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Created on: 11 Mar 2016, author John Beard
 * Copyright (C) 1992-2016 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "array_creator.h"

#include <array_pad_name_provider.h>
#include <board_commit.h>
#include <pad_naming.h>

#include <dialogs/dialog_create_array.h>

/**
 * Transform a #BOARD_ITEM from the given #ARRAY_OPTIONS and an index into the array.
 *
 * @param aArrOpts The array options that describe the array
 * @param aIndex   The index in the array of this item
 * @param aItem    The item to transform
 */
static void TransformItem( const ARRAY_OPTIONS& aArrOpts, int aIndex, BOARD_ITEM& aItem )
{
    const ARRAY_OPTIONS::TRANSFORM transform = aArrOpts.GetTransform( aIndex, aItem.GetPosition() );

    aItem.Move( (wxPoint) transform.m_offset );
    aItem.Rotate( aItem.GetPosition(), transform.m_rotation * 10 );
}


void ARRAY_CREATOR::Invoke()
{
    // bail out if no items
    if( m_selection.Size() == 0 )
        return;

    MODULE* const module = m_editModules ? m_parent.GetBoard()->GetFirstModule() : nullptr;

    const bool enableArrayNumbering = m_editModules;
    const wxPoint rotPoint = (wxPoint) m_selection.GetCenter();

    std::unique_ptr<ARRAY_OPTIONS> array_opts;

    DIALOG_CREATE_ARRAY dialog( &m_parent, array_opts, enableArrayNumbering, rotPoint );

    int ret = dialog.ShowModal();

    if( ret != wxID_OK || array_opts == NULL )
        return;

    BOARD_COMMIT commit( &m_parent );

    ARRAY_PAD_NAME_PROVIDER pad_name_provider( module, *array_opts );

    for ( int i = 0; i < m_selection.Size(); ++i )
    {
        BOARD_ITEM* item = static_cast<BOARD_ITEM*>( m_selection[ i ] );

        if( item->Type() == PCB_PAD_T && !m_editModules )
        {
            // If it is not the module editor, then duplicate the parent module instead
            item = static_cast<MODULE*>( item )->GetParent();
        }

        // The first item in list is the original item. We do not modify it
        for( int ptN = 0; ptN < array_opts->GetArraySize(); ptN++ )
        {
            BOARD_ITEM* this_item;

            if( ptN == 0 )
            {
                // the first point: we don't own this or add it, but
                // we might still modify it (position or label)
                this_item = item;
            }
            else
            {
                // Need to create a new item
                std::unique_ptr<BOARD_ITEM> new_item;

                if( m_editModules )
                {
                    // Don't bother incrementing pads: the module won't update
                    // until commit, so we can only do this once
                    new_item.reset( module->Duplicate( item, false ) );
                }
                else
                {
                    new_item.reset( m_parent.GetBoard()->Duplicate( item ) );

                    // PCB items keep the same numbering

                    // @TODO: renumber modules if asked. This needs UI to enable.
                    // something like this, but needs a "block offset" to prevent
                    // multiple selections overlapping.
                    // if( new_item->Type() == PCB_MODULE_T )
                    //     static_cast<MODULE&>( *new_item ).IncrementReference( ptN );

                    // @TODO: we should merge zones. This is a bit tricky, because
                    // the undo command needs saving old area, if it is merged.
                }

                this_item = new_item.get();

                if( new_item )
                {
                    // Because aItem is/can be created from a selected item, and inherits from
                    // it this state, reset the selected stated of aItem:
                    this_item->ClearSelected();

                    if( this_item->Type() == PCB_MODULE_T )
                    {
                        static_cast<MODULE*>( this_item )->RunOnChildren( [&] ( BOARD_ITEM* aItem )
                        {
                            aItem->ClearSelected();
                        });
                    }

                    commit.Add( new_item.release() );
                }
            }

            // always transform the item
            if( this_item )
            {
                commit.Modify( this_item );
                TransformItem( *array_opts, ptN, *this_item );
            }

            // attempt to renumber items if the array parameters define
            // a complete numbering scheme to number by (as opposed to
            // implicit numbering by incrementing the items during creation
            if( this_item && array_opts->ShouldNumberItems() )
            {
                // Renumber non-aperture pads.
                if( this_item->Type() == PCB_PAD_T )
                {
                    auto& pad = static_cast<D_PAD&>( *this_item );

                    if( PAD_NAMING::PadCanHaveName( pad ) )
                    {
                        wxString newName = pad_name_provider.GetNextPadName();
                        pad.SetName( newName );
                    }
                }
            }
        }
    }

    commit.Push( _( "Create an array" ) );
}
