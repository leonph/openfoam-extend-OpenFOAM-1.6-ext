/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::refineCell

Description
    Container with cells to refine. Refinement given as single direction.

SourceFiles
    refineCell.C

\*---------------------------------------------------------------------------*/

#ifndef refineCell_H
#define refineCell_H

#include "label.H"
#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class Istream;
class Ostream;

/*---------------------------------------------------------------------------*\
                           Class refineCell Declaration
\*---------------------------------------------------------------------------*/

class refineCell
{
    // Private data

    //- Cell label
    label cellNo_;

    //- Preferred refinement direction (always normalized).
    vector direction_;

public:

    // Constructors

        //- Null
        refineCell();

        //- from components. Vector will be normalized upon construction.
        refineCell(const label, const vector&);

        //- from Istream. Vector will be normalized upon construction.
        refineCell(Istream& is);


    // Member Functions

        label cellNo() const
        {
            return cellNo_;
        }

        const vector& direction() const
        {
            return direction_;
        }


    // Friend Operators

        inline friend bool operator==
        (
            const refineCell& rc1,
            const refineCell& rc2
        )
        {
            return (rc1.cellNo() == rc2.cellNo());
        }

        inline friend bool operator!=
        (
            const refineCell& rc1,
            const refineCell& rc2
        )
        {
            return !(rc1 == rc2);
        }


    // IOstream Operators

        friend Ostream& operator<<(Ostream&, const refineCell&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

