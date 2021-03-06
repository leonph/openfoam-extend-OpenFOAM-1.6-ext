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
    Foam::valveBank

Description
    A list of valves.

\*---------------------------------------------------------------------------*/

#ifndef valveBank_H
#define valveBank_H

#include "PtrList.H"
#include "engineValve.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class valveBank Declaration
\*---------------------------------------------------------------------------*/

class valveBank
:
    public PtrList<engineValve>
{
private:

    // Private Member Functions

        //- Disallow default bitwise copy construct
        valveBank(const valveBank&);

        //- Disallow default bitwise assignment
        void operator=(const valveBank&);


public:

    // Constructors

        //- Construct from Istream
        valveBank
        (
            const polyMesh& mesh,
            Istream& is
        )
        {
            PtrList<entry> valveEntries(is);

            setSize(valveEntries.size());

            forAll (valveEntries, valveI)
            {
                this->set
                (
                    valveI,
                    new engineValve
                    (
                        valveEntries[valveI].keyword(),
                        mesh,
                        valveEntries[valveI].dict()
                    )
                );
            }
        }


    // Destructor - default


    // Member Functions
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
