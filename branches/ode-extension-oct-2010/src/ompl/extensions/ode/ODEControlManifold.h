/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2010, Rice University
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Rice University nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Ioan Sucan */

#ifndef OMPL_EXTENSION_ODE_CONTROL_MANIFOLD_
#define OMPL_EXTENSION_ODE_CONTROL_MANIFOLD_

#include "ompl/control/manifolds/RealVectorControlManifold.h"
#include "ompl/extensions/ode/ODEStateManifold.h"

namespace ompl
{

    namespace control
    {
	
	class ODEControlManifold : public RealVectorControlManifold
	{
	public:
	    
	    ODEControlManifold(const base::StateManifoldPtr &stateManifold) : 
		RealVectorControlManifold(stateManifold, stateManifold->as<ODEStateManifold>()->getEnvironment().getControlDimension())
	    {
		contactGroup_ = dJointGroupCreate(0);
		RealVectorBounds bounds(dimension_);
		stateManifold->as<ODEStateManifold>()->getEnvironment().getControlBounds(bounds.low, bounds.high);
		setBounds(bounds);
	    }
	    
	    virtual ~ODEControlManifold(void)
	    {
		dJointGroupDestroy(contactGroup_);
	    }
	    
	    virtual bool canPropagateBackward(void) const
	    {
		return false;
	    }
	    
	    virtual PropagationResult propagate(const base::State *state, const Control* control, const double duration, base::State *result) const;
	    
	protected:
	    
	    mutable dJointGroupID contactGroup_;
	};
    }

}


#endif
