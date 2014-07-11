/*
 * GHOST (General meta-Heuristic Optimization Solving Tool) is a C++ library 
 * designed for StarCraft: Brood war. 
 * GHOST is a meta-heuristic solver aiming to solve any kind of combinatorial 
 * and optimization RTS-related problems represented by a CSP/COP. 
 * It is a generalization of the project Wall-in.
 * Please visit https://github.com/richoux/GHOST for further information.
 * 
 * Copyright (C) 2014 Florian Richoux
 *
 * This file is part of GHOST.
 * GHOST is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * GHOST is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with GHOST. If not, see http://www.gnu.org/licenses/.
 */


#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

#include "../../include/constraints/buildorderConstraint.hpp"

using namespace std;

namespace ghost
{
  BuildOrderConstraint::BuildOrderConstraint( const vector< Action > *variables, const BuildOrderDomain *domain )
    : Constraint<Action, BuildOrderDomain>(variables, domain) { }


  double BuildOrderConstraint::v_cost( vector<double> &varCost ) const
  {
    double conflicts = 0.;
    auto vecOrder = domain->getOrder();
    for( auto it = begin(vecOrder) ; it != end(vecOrder) ; ++it )
    {
      int value = it->getValue();
      for( const auto &d : it->getDependencies() )
      {
	vector<Action> dependencies( vecOrder.size() );
	auto iter = copy_if( begin(vecOrder), end(vecOrder), begin(dependencies), [&](Action a){return d.compare(a.getName()) == 0;} );
	dependencies.resize( std::distance( begin(dependencies), iter ) );

	if( dependencies.empty() )
	{
	  Action newAction = factoryAction( d );

	  newAction.setValue( value );
	  domain->addAction( newAction, true );

	  for( auto &v : *variables )
	    if( v.getValue() >= value )
	      v.shiftValue();
	    
	  variables->push_back( newAction );
	  varCost.push_back(1);
	  ++conflicts;
	}
	else
	  if( none_of( begin(dependencies), end(dependencies), [&](Action a){return a.getValue() < value;} ) )
	  {
	    varCost.at( it->getId() ) += 3;
	    conflicts += 3;
	    for( const auto &dep : dependencies )
	    {
	      varCost.at( dep.getId() ) += 2;
	      conflicts += 2;
	    }
	  }
      }
    }

    return conflicts;
  }
}
