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
    Foam::midPoint

Description
    Mid-point interpolation (weighting factors = 0.5) scheme class.

SourceFiles
    midPoint.C

\*---------------------------------------------------------------------------*/

#ifndef midPoint_H
#define midPoint_H

#include "surfaceInterpolationScheme.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class midPoint Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class midPoint
:
    public surfaceInterpolationScheme<Type>
{
    // Private Member Functions

        //- Disallow default bitwise assignment
        void operator=(const midPoint&);


public:

    //- Runtime type information
    TypeName("midPoint");


    // Constructors

        //- Construct from mesh
        midPoint(const fvMesh& mesh)
        :
            surfaceInterpolationScheme<Type>(mesh)
        {}

        //- Construct from Istream
        midPoint(const fvMesh& mesh, Istream&)
        :
            surfaceInterpolationScheme<Type>(mesh)
        {}

        //- Construct from faceFlux and Istream
        midPoint
        (
            const fvMesh& mesh,
            const surfaceScalarField&,
            Istream&
        )
        :
            surfaceInterpolationScheme<Type>(mesh)
        {}


    // Member Functions

        //- Return the interpolation weighting factors
        tmp<surfaceScalarField> weights
        (
            const GeometricField<Type, fvPatchField, volMesh>&
        ) const
        {
            tmp<surfaceScalarField> taw
            (
                new surfaceScalarField
                (
                    IOobject
                    (
                        "midPointWeights",
                        this->mesh().time().timeName(),
                        this->mesh()
                    ),
                    this->mesh(),
                    dimensionedScalar("0.5", dimless, 0.5)
                )
            );

            surfaceScalarField::GeometricBoundaryField& awbf =
                taw().boundaryField();

            forAll(awbf, patchi)
            {
                if (!awbf[patchi].coupled())
                {
                    awbf[patchi] = 1.0;
                }
            }

            return taw;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
