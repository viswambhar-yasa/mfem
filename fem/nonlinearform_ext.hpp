// Copyright (c) 2010-2020, Lawrence Livermore National Security, LLC. Produced
// at the Lawrence Livermore National Laboratory. All Rights reserved. See files
// LICENSE and NOTICE for details. LLNL-CODE-806117.
//
// This file is part of the MFEM library. For more information and source code
// availability visit https://mfem.org.
//
// MFEM is free software; you can redistribute it and/or modify it under the
// terms of the BSD-3 license. We welcome feedback and contributions, see file
// CONTRIBUTING.md for details.

#ifndef NONLINEARFORM_EXT_HPP
#define NONLINEARFORM_EXT_HPP

#include "../config/config.hpp"
#include "fespace.hpp"

namespace mfem
{
class NonlinearForm;

class NonlinearFormExtension : public Operator
{
protected:
   const NonlinearForm *nlf;

public:
   NonlinearFormExtension(const NonlinearForm*);
   virtual void Assemble() = 0;
   virtual Operator &GetGradient(const Vector&) const = 0;
};


/// Data and methods for partially-assembled nonlinear forms
class PANonlinearFormExtension : public NonlinearFormExtension
{
protected:
   mutable OperatorPtr GradOp;
   const FiniteElementSpace &fes;
   mutable Vector localX, localY;
   const Operator *elem_restrict_lex;

public:
   PANonlinearFormExtension(NonlinearForm *nlf);
   void Assemble();
   void Mult(const Vector &, Vector &) const;
   Operator &GetGradient(const Vector&) const;
};


class PAGradOperator : public Operator
{
protected:
   const NonlinearForm *nlf;
   const FiniteElementSpace &fes;
   mutable Vector Xe, Re, Ce;
   const Array<int> &ess_tdof_list;
   const Operator *elem_restrict_lex;
public:
   PAGradOperator(const Vector &x,
                  const NonlinearForm *nlf,
                  const FiniteElementSpace &fes,
                  const Array<int> &ess_tdof_list,
                  const Operator *elem_restrict_lex);
   void Mult(const Vector &, Vector &) const;
};

} // namespace mfem

#endif // NONLINEARFORM_EXT_HPP
