/*
 * GHOST (General meta-Heuristic Optimization Solving Tool) is a C++ library 
 * designed to help developers to model and implement optimization problem 
 * solving. 
 * GHOST is a meta-heuristic solver aiming to solve any kind of combinatorial 
 * and optimization real-time problems represented by a CSP/COP. 
 * GHOST has been first developped to help making AI for the RTS game
 * StarCraft: Brood war, but can be used for any kind of applications where 
 * solving combinatorial and optimization problems within some tenth of 
 * milliseconds is needed. It is a generalization of the Wall-in project.
 * Please visit https://github.com/richoux/GHOST for further information.
 * 
 * Copyright (C) 2014-2016 Florian Richoux
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


#pragma once

#include <random>
#include <unistd.h>

namespace ghost
{
  //! Random is the class coding pseudo-random generators used in GHOST
  /*!
   * Random use the C++11 Mersenne Twister (mt19937) as a
   * pseudo-random generator.
   *
   * Seeds are generated by C++11 std::random_device.
   */
  class Random
  {
  public:
    Random() : rng( rd() ) { }
    // Random( const Random &other ) : Random() { }

    // Random operator=( const Random &other ) { return Random(); }

    //! Inline function to return a random value in [0, limit[
    /*!
     * getRandNum uses a std::uniform_int_distribution<int> to compute
     * and return a pseudo-random value from the range [0, limit[
     *
     * \param limit The upper bound of the range [0, limit[ from where a random value is computed.
     * \return A pseudo-random value in the range [0, limit[
     */
    inline int getRandNum( int limit ) { return ( numbers(rng) % limit ); } 

  private:
    std::random_device			rd;
    std::mt19937			rng;
    std::uniform_int_distribution<int>  numbers;
  };
}
