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
    Foam::ICCG

Description
    Incomplete Cholesky preconditioned CG solver derived from the general
    preconditioned CG solver PCG but with the choice of preconditioner
    pre-selected.

Deprecated
    This solver is present for backward-compatibility and the PCG solver
    should be used for preference.

SourceFiles
    ICCG.C

\*---------------------------------------------------------------------------*/

#ifndef ICCG_H
#define ICCG_H

#include "PCG.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class ICCG Declaration
\*---------------------------------------------------------------------------*/

class ICCG
:
    public PCG
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        ICCG(const ICCG&);

        //- Disallow default bitwise assignment
        void operator=(const ICCG&);

public:

        //- Return the dictionary constructed from the components.
        //  Needed for backward compatibility
        static dictionary solverDict
        (
            const scalar tol,
            const scalar relTol
        );

        //- Return the dictionary constructed from the old-style data-stream.
        //  Needed for backward compatibility
        static dictionary solverDict(Istream&);


    //- Runtime type information
    TypeName("ICCG");


    // Constructors

        //- Construct from matrix components and solver data stream
        ICCG
        (
            const word& fieldName,
            const lduMatrix& matrix,
            const FieldField<Field, scalar>& coupleBouCoeffs,
            const FieldField<Field, scalar>& coupleIntCoeffs,
            const lduInterfaceFieldPtrsList& interfaces,
            const dictionary& dict
        );

        //- Construct from matrix components and tolerances
        ICCG
        (
            const word& fieldName,
            const lduMatrix& matrix,
            const FieldField<Field, scalar>& coupleBouCoeffs,
            const FieldField<Field, scalar>& coupleIntCoeffs,
            const lduInterfaceFieldPtrsList& interfaces,
            const scalar tolerance,
            const scalar relTol = 0.0
        );

    // Destructor

        virtual ~ICCG()
        {}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
