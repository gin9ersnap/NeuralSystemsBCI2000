# -*- coding: utf-8 -*-
# 
#   $Id$
#   
#   This file is part of the BCPy2000 framework, a Python framework for
#   implementing modules that run on top of the BCI2000 <http://bci2000.org/>
#   platform, for the purpose of realtime biosignal processing.
# 
#   Copyright (C) 2007-11  Jeremy Hill, Thomas Schreiner,
#                          Christian Puzicha, Jason Farquhar
#   
#   bcpy2000@bci2000.org
#   
#   The BCPy2000 framework is free software: you can redistribute it
#   and/or modify it under the terms of the GNU General Public License
#   as published by the Free Software Foundation, either version 3 of
#   the License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
import numpy
import time
import DataFiles
import Parameters

try: import SigTools
except ImportError: import BCPy2000.SigTools as SigTools

def ClassifyERPs (
		featurefiles,
		C = (10.0, 1.0, 0.1, 0.01),
		gamma = (1.0, 0.8, 0.6, 0.4, 0.2, 0.0),
		keepchan = (),
		rmchan = (),
		rmchan_usualsuspects = ('AUDL','AUDR','LAUD','RAUD','SYNC','VSYNC', 'VMRK', 'OLDREF'),
		rebias = True,
		save = False,
		description='ERPs to attended vs unattended events',
		maxcount=None,
		classes=None,
		folds=None,
	):

	d = DataFiles.load(featurefiles, catdim=0, maxcount=maxcount)

	x = d['x']
	y = numpy.array(d['y'].flat)
	if classes != None:
		for cl in classes:
			if cl not in y: raise ValueError("class %s is not in the dataset" % str(cl))
		mask = numpy.array([yi in classes for yi in y])
		y = y[mask]
		x = x[mask]
		discarded = sum(mask==False)
		if discarded: print "discarding %d trials that are outside the requested classes %s"%(discarded,str(classes))
		
	n = len(y)
	uy = numpy.unique(y)
	if uy.size != 2: raise ValueError("expected 2 classes in dataset, found %d : %s" % (uy.size, str(uy)))
	y = numpy.sign(y - uy.mean())

	cov,trchvar = SigTools.spcov(x=x, y=y, balance=False, return_trchvar=True) # NB: symwhitenkern would not be able to balance
	
	starttime = time.time()
	
	chlower = [ch.lower() for ch in d['channels']]
	if keepchan in [None,(),'',[]]:
		if isinstance(rmchan, basestring): rmchan = rmchan.split()
		if isinstance(rmchan_usualsuspects, basestring): rmchan_usualsuspects = rmchan_usualsuspects.split()
		allrmchan = [ch.lower() for ch in list(rmchan)+list(rmchan_usualsuspects)]
		unwanted = numpy.array([ch in allrmchan for ch in chlower])
		notfound = [ch for ch in rmchan if ch.lower() not in chlower]
	else:
		if isinstance(keepchan, basestring): keepchan = keepchan.split()
		lowerkeepchan = [ch.lower() for ch in keepchan]
		unwanted = numpy.array([ch not in lowerkeepchan for ch in chlower])
		notfound = [ch for ch in keepchan if ch.lower() not in chlower]
		
	wanted = numpy.logical_not(unwanted)
	print ' '
	if len(notfound): print "WARNING: could not find channel%s %s\n" % ({1:''}.get(len(notfound),'s'), ', '.join(notfound))
	removed = [ch for removing,ch in zip(unwanted, d['channels']) if removing]
	if len(removed): print "removed %d channel%s (%s)" % (len(removed), {1:''}.get(len(removed),'s'), ', '.join(removed))
	print "classification will be based on %d channel%s" % (sum(wanted), {1:''}.get(sum(wanted),'s'))
	print "%d negatives + %d positives = %d exemplars" % (sum(y<0), sum(y>0), n)
	print ' '
	
	x[:, unwanted, :] = 0
	cov[:, unwanted] = 0
	cov[unwanted, :] = 0
	nu = numpy.asarray(cov).diagonal()[wanted].mean()
	for i in range(len(cov)):
		if cov[i,i] == 0: cov[i,i] = nu
	
	if not isinstance(C, (tuple,list,numpy.ndarray,type(None))): C = [C]
	if not isinstance(gamma, (tuple,list,numpy.ndarray,type(None))): gamma = [gamma]

	c = SigTools.klr2class(lossfunc=SigTools.balanced_loss, relcost='balance')
	c.varyhyper({})
	if c != None: c.hyper.C=list(C)
	if gamma == None: c.hyper.kernel.func = SigTools.linkern
	else: c.varyhyper({'kernel.func':SigTools.symwhitenkern, 'kernel.cov':[cov], 'kernel.gamma':list(gamma)})
	c.cvtrain(x=x, y=y, folds=folds)
	if rebias: c.rebias()
	c.calibrate()

	chosen = c.cv.chosen.hyper
	if gamma == None:
		Ps = None
		Gp = c.featureweight(x=x)
	else:
		Ps = SigTools.svd(SigTools.shrinkcov(cov, copy=True, gamma=chosen.kernel.gamma)).isqrtm
		xp = SigTools.spfilt(x, Ps.H, copy=True)
		Gp = c.featureweight(x=xp)
	
	u = SigTools.stfac(Gp, Ps)
	u.channels = d['channels']
	u.channels_used = wanted
	u.fs = d['fs']
	u.trchvar = trchvar
	
	elapsed = time.time() - starttime
	minutes = int(elapsed/60.0)
	seconds = int(round(elapsed - minutes * 60.0))
	print '%d min %d sec' % (minutes, seconds)
	datestamp = time.strftime('%Y-%m-%d %H:%M:%S')
	csummary = '%s (%s) trained on %d (CV %s = %.3f) at %s' % (
		c.__class__.__name__,
		SigTools.experiment()._shortdesc(chosen),
		sum(c.input.istrain),
		c.loss.func.__name__,
		c.loss.train,
		datestamp,
	)
	description = 'binary classification of %s: %s' % (description, csummary)
	u.description = description
	
	if save:
		if not isinstance(save, basestring):
			save = featurefiles
			if isinstance(save, (tuple,list)): save = save[-1]
			if save.lower().endswith('.gz'): save = save[:-3]
			if save.lower().endswith('.pk'): save = save[:-3]
			save = save + '_weights.prm'
		print "\nsaving %s\n" % save
		Parameters.Param(u.G.A, name='ERPClassifierWeights', tab='PythonSig', section='Epoch', comment=csummary).writeto(save)
		Parameters.Param(c.model.bias, name='ERPClassifierBias', tab='PythonSig', section='Epoch', comment=csummary).appendto(save)
		Parameters.Param(description, name='SignalProcessingDescription', tab='PythonSig').appendto(save)
	return u,c
