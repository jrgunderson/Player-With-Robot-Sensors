/***************************************************************************
 *   Copyright (C) 2009 by Markus Bader                                    *
 *   bader@acin.tuwien.ac.at                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.             *
 ***************************************************************************/


#include "mex.h"
#include <vector>
#include <map>
#include <libplayerc++/playerc++.h>
#include "cpointers.h"

void mexFunction ( int nlhs, mxArray *plhs[], int nrhs,  const mxArray *prhs[] ) {
    if (nrhs != 2  || ! mxIsNumeric (prhs[0]) || ! mxIsNumeric (prhs[1])) {
        mexPrintf("usage: laser = %s ( client, index )\n", mexFunctionName());
				mexErrMsgTxt ("Wrong command");
    }
    double index = *mxGetPr(prhs[1]);
    PlayerCc::PlayerClient *pRobot =  getCPointer<PlayerCc::PlayerClient>(prhs[0]);
    PlayerCc::LaserProxy *pLaser = new PlayerCc::LaserProxy(pRobot, (int) index);
    plhs[0] = setCPointer(pLaser);
}
