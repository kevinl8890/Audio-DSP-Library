/*
 *  BiquadAllPass.cpp
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BiquadAllPass.h"


/*
 
 A  = sqrt( 10^(dBgain/20) )
 =       10^(dBgain/40)  
 
 w0 = 2*pi*f0/Fs
 
 alpha = sin(w0)/(2*Q)    
 
 APF:        H(s) = (s^2 - s/Q + 1) / (s^2 + s/Q + 1)
 
 b0 =   1 - alpha
 b1 =  -2*cos(w0)
 b2 =   1 + alpha
 a0 =   1 + alpha
 a1 =  -2*cos(w0)
 a2 =   1 - alpha
 
 
 
 
 *in + s->b[1]*h->v[0] + s->b[2]*h->v[1] + s->a[1]*h->v[2] + s->a[2]*h->v[3];
 
 void SetStage    ( CalcT a1, CalcT a2, CalcT b0, CalcT b1, CalcT b2 );
 
 */


void BiquadAllPass::Setup            ( Float32 normFreq,Float32 q ){

	Float32 w0 = 2 * M_PI * normFreq;
	Float32 cs = cos(w0);
	Float32 sn = sin(w0);
	SetupCommon( sn, cs, q );

}


void BiquadAllPass::SetupFast        ( Float32 normFreq, Float32 q ){


	Float32 w0 = 2 * M_PI * normFreq;
	Float32 sn, cs;
	fastsincos( w0, &sn, &cs );
	SetupCommon( sn, cs, q );
}


void BiquadAllPass::SetupCommon    ( Float32 sn, Float32 cs, Float32 q ){

	Float32 alph = sn / ( 2 * q );
	Float32 b2 =  1 + alph;
	Float32 a0 =  1 / b2;
	Float32 b0 =( 1 - alph ) * a0;
	Float32 b1 = -2 * cs * a0;
	this->SetStage( -b1, -b0, b0, b1, b2*a0 );


}

