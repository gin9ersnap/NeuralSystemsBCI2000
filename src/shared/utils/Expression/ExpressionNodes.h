//////////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: juergen.mellinger@uni-tuebingen.de
// Description: A collection of classes that represent nodes of parsed expressions.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2012: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
//////////////////////////////////////////////////////////////////////////////////////
#ifndef EXPRESSION_NODES_H
#define EXPRESSION_NODES_H

#include <vector>
#include <string>

namespace ExpressionParser
{

class RefObj
{
 public:
  RefObj() : mRefs( 0 ) {}
  RefObj( const RefObj& other ) : mRefs( 0 ) {}
  RefObj& operator=( const RefObj& ) { return *this; }
  virtual ~RefObj();
  void AddRef() { ++mRefs; }
  void Release() { if( !--mRefs ) delete this; }
  int Refs() const { return mRefs; }
 private:
  int mRefs;
};

class ObjPtr
{
 public:
  ObjPtr( RefObj* p = 0 ) : mp( p ) { Inc(); }
  ObjPtr( const ObjPtr& p ) : mp( p.mp ) { Inc(); }
  ObjPtr& operator=( const ObjPtr& p ) { p.Inc(); this->Dec(); mp = p.mp; return *this; }
  ~ObjPtr() { Dec(); }
  RefObj* operator->() { return mp; }
  const RefObj* operator->() const { return mp; }
  operator bool() const { return mp; }
 private:
  void Inc() const { if( mp ) mp->AddRef(); }
  void Dec() const { if( mp ) mp->Release(); }
  RefObj* mp;
};

class Node;
class NodePtr;
class NodeList : public RefObj
{
 public:
  NodeList() {}
  NodeList( Node* p ) { Add( p ); }
  NodeList& Add( Node* );
  int Size() const { return static_cast<int>( mList.size() ); }
  size_t size() const { return mList.size(); }
  void Clear() { mList.clear(); }
  Node* operator[]( size_t idx ) const;
  NodePtr& operator[]( size_t idx ) { return mList[idx]; }

 private:
  std::vector<NodePtr> mList;
};

class Node : public RefObj
{
 public:
  Node( bool isConst = false );
  virtual ~Node();

  bool IsConst() const { return mIsConst; }

  Node* Simplify();
  double Evaluate() { return OnEvaluate(); }

 protected:
  void Add( Node* );

 protected:
  virtual Node* OnSimplify() { return this; }
  virtual double OnEvaluate() = 0;

 protected:
  std::vector<NodePtr> mChildren;
  bool mIsConst;
};

class NodePtr
{
 public:
  NodePtr( Node* p = 0 ) : mPtr( p ), mp( p ) {}
  Node* operator->() { return mp; }
  const Node* operator->() const { return mp; }
  operator Node*() { return mp; }
  operator const Node*() const { return mp; }
 private:
  Node* mp;
  ObjPtr mPtr;
};

class ConstantNode : public Node
{
 public:
  ConstantNode( double value ) : Node( true ), mValue( value ) {}

 protected:
  double OnEvaluate() { return mValue; }

 private:
  double mValue;
};

class VariableNode : public Node
{
 public:
  VariableNode( double& valueRef ) : mrValue( valueRef ) {}

 protected:
  double OnEvaluate() { return mrValue; }

 private:
  double& mrValue;
};

class AssignmentNode : public Node
{
 public:
  AssignmentNode( double& valueRef, Node* rhs ) : mrValue( valueRef ) { Add( rhs ); }

 protected:
  double OnEvaluate() { return ( mrValue = mChildren[0]->Evaluate() ); }

private:
 double& mrValue;
};

class ConstPropagatingNode : public Node
{
 public:
  ConstPropagatingNode( bool doPropagate = false ) : mPropagate( doPropagate ) {}
  Node* OnSimplify();

 private:
  bool mPropagate;
};

template<int N>
class FunctionNode {};

template<>
class FunctionNode<0> : public ConstPropagatingNode
{
 public:
  typedef double ( *Pointer )();
  FunctionNode( bool c, Pointer f ) : ConstPropagatingNode( c ), p( f ) {}

 protected:
  double OnEvaluate() { return p(); }

 private:
  Pointer p;
};

template<>
class FunctionNode<1> : public ConstPropagatingNode
{
 public:
  typedef double ( *Pointer )( double );
  FunctionNode( bool c, Pointer f, Node* arg1 ) : ConstPropagatingNode( c ), p( f ) { Add( arg1 ); }

 protected:
  double OnEvaluate() { return p( mChildren[0]->Evaluate() ); }

 private:
  Pointer p;
};

template<>
class FunctionNode<2> : public ConstPropagatingNode
{
 public:
  typedef double ( *Pointer )( double, double );
  FunctionNode( bool c, Pointer f, Node* arg1, Node* arg2 ) : ConstPropagatingNode( c ), p( f ) { Add( arg1 ); Add( arg2 ); }

 protected:
  double OnEvaluate() { return p( mChildren[0]->Evaluate(), mChildren[1]->Evaluate() ); }

 private:
  Pointer p;
};

template<>
class FunctionNode<3> : public ConstPropagatingNode
{
 public:
  typedef double ( *Pointer )( double, double, double );
  FunctionNode( bool c, Pointer f, Node* arg1, Node* arg2, Node* arg3 ) : ConstPropagatingNode( c ), p( f ) { Add( arg1 ); Add( arg2 ); Add( arg3 ); }

 protected:
  double OnEvaluate() { return p( mChildren[0]->Evaluate(), mChildren[1]->Evaluate(), mChildren[2]->Evaluate() ); }

 private:
  Pointer p;
};

class StringNode : public Node
{
 public:
  StringNode( const std::string& s ) : mString( s ) { mIsConst = true; }
  const std::string& Evaluate() { OnEvaluate(); return mString; }

 protected:
  double OnEvaluate();
  std::string mString;
};

class AddressNode : public StringNode
{
 public:
  AddressNode( Node*, Node* );

 protected:
  double OnEvaluate();
  Node* OnSimplify();
};

} // namespace ExpressionNodes

#endif // EXPRESSION_NODES_H

