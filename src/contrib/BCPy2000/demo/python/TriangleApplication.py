#   $Id$
#   
#   This file is a BCPy2000 demo file, which illustrates the capabilities
#   of the BCPy2000 framework.
# 
#   Copyright (C) 2007-9  Jeremy Hill
#   
#   bcpy2000@bci2000.org
#   
#   This program is free software: you can redistribute it
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
from random import randint

from AppTools.Boxes import box
from AppTools.Displays import fullscreen
from AppTools.Shapes import PolygonTexture, Disc
from AppTools.StateMonitors import addstatemonitor, addphasemonitor

# from pygame import mixer; from pygame.mixer import Sound
# from WavTools.FakePyGame import mixer, Sound # would provide a workalike interface to the line above
                                               #
import WavTools                                # but let's get into the habit of using WavTools.player
                                               # explicitly, since it is more flexible, and its timing
                                               # is now more reliable than that of pygame.mixer.Sound

#################################################################
#################################################################

class BciApplication(BciGenericApplication):
	
	#############################################################
	
	def Description(self):
		return "the techno triangle"
	
	#############################################################
	
	def Construct(self):
		self.define_param(
			"PythonApp:Design   int    AlternateTargets=    0     0     0   1  // alternate target classes rather than choosing randomly (boolean)",
			"PythonApp:Design   int    ShowFixation=        0     0     0   1  // show a fixation point in the center (boolean)",
			"PythonApp:Screen   int    ScreenId=           -1    -1     %   %  // on which screen should the stimulus window be opened - use -1 for last",
			"PythonApp:Screen   float  WindowSize=         0.8   1.0   0.0 1.0 // size of the stimulus window, proportional to the screen",
			"PythonApp:Stimuli  float  CircleRadius=       1.0   1.0   0.0 5.0 // size of the background circle",
			"PythonApp:Stimuli  float  OuterTriangleSize=  0.9   1.0   0.0 1.0 // size of the outer triangle",
			"PythonApp:Stimuli  float  InnerTriangleSize=  0.2   0.2   0.0 0.5 // size of the target triangles relative to the outer triangle",
			"PythonApp:Feedback int    CursorFeedback=      1     1     0   1  // show online feedback cursor (boolean)",
			"PythonApp:Feedback int    ColorFeedback=       1     0     0   1  // adapt background circle color to feedback? (boolean)",
			"PythonApp:Feedback int    AudioFeedback=       1     0     0   1  // play continuous sounds? (boolean)",
			"PythonApp:Feedback matrix FeedbackWavs=   3 1 feedback-drums.wav feedback-piano.wav feedback-strings.wav % % % // feedback wavs",
		)
		self.define_state(
			"DistanceFromCorner1   8 0 0 0",
			"DistanceFromCorner2   8 0 0 0",
			"DistanceFromCorner3   8 0 0 0",
			"DistanceFromCenter    8 0 0 0",
			"Angle                 9 0 0 0",

			"BaselineOn   1 0 0 0",
			"StartCueOn   1 0 0 0",
			"StopCueOn    1 0 0 0",
			"Learn        1 0 0 0",   # should the signal-processing module be taking notice?
			"TargetClass  2 0 0 0",   # should the subject be imagining feet (1), left hand (2), right hand (3), or resting (0 during 'baseline' phase) ?
			"FeedbackOn   1 0 0 0",   # bells? whistles?
		)
	
	#############################################################
	
	def Preflight(self, sigprops):
		
		self.nclasses = 3
		
		if int(self.params['AudioFeedback']) and len(self.params['FeedbackWavs']) != self.nclasses:
			raise EndUserError, 'FeedbackWavs matrix should have %d rows' % self.nclasses
		
		if not self.in_signal_dim[0] in (self.nclasses, self.nclasses+1):
			raise EndUserError,'%d- or %d-channel input expected' % (self.nclasses,self.nclasses+1)

		siz = float(self.params['WindowSize'])
		screenid = int(self.params['ScreenId'])  # ScreenId 0 is the first screen, 1 the second, -1 the last
		fullscreen(scale=siz, id=screenid, frameless_window=(siz==1))
		# only use a borderless window if the window is set to fill the whole screen
		
	#############################################################
	
	def Initialize(self, indim, outdim):
				
		# compute how big everything should be
		itf = float(self.params['InnerTriangleSize'])
		otf = float(self.params['OuterTriangleSize'])
		scrw,scrh = self.screen.size
		scrsiz = min(scrw,scrh)
		circle_radius = scrsiz * 0.5 * float(self.params['CircleRadius'])
		siz = (scrsiz * otf * 0.866,   scrsiz * otf * 0.75)
		
		# use a handy AppTools.Boxes.box object as the coordinate frame for the triangle
		b = box(size=siz, position=(scrw/2.0,scrh/2.0 - siz[1]/6.0), sticky=True)
		center = b.map((0.5,2.0/3.0), 'position')
		self.positions = {'origin': numpy.matrix(center)}
		
		# draw the main triangle
		triangle = PolygonTexture(frame=b, vertices=((0,1),(1,1),(0.5,0)), color=(0,0,0,0.5))
		
		# the red target triangle
		b.anchor='bottom'
		b.scale(itf)
		self.positions['red'] = numpy.matrix(b.position)
		red = PolygonTexture(frame=b, vertices=((0,1),(1,1),(0.5,0)), color=(1,0.1,0.1))
		b.scale(1.0 / itf)

		# the green target triangle
		b.anchor='upperleft'
		b.scale(itf)
		self.positions['green'] = numpy.matrix(b.position)
		green = PolygonTexture(frame=b, vertices=((0,1),(1,1),(0.5,0)), color=(0.1,1,0.1))
		b.scale(1.0 / itf);

		# the blue target triangle
		b.anchor='upperright'
		b.scale(itf)
		self.positions['blue'] = numpy.matrix(b.position)
		blue = PolygonTexture(frame=b, vertices=((0,1),(1,1),(0.5,0)), color=(0.1,0.1,1))
		b.scale(1.0 / itf);

		# and the arrow
		b.anchor='center'
		fac = (0.25,0.4)
		b.scale(fac)
		arrow = PolygonTexture(frame=b, vertices=((0.22,0.35),(0,0.35),(0.5,0),(1,0.35),(0.78,0.35),(0.78,0.75),(0.22,0.75),), color=(1,1,1), on=False, position=center)
		b.scale((1.0/fac[0],1.0/fac[1]))
				
		# store the significant points on the screen for later use
		self.p = numpy.concatenate((self.positions['red'],self.positions['green'],self.positions['blue']), axis=0)

		# let's have a black background
		self.screen.color = (0,0,0)
		
		# OK, now register all those stimuli, plus a few more, with the framework
		self.stimulus('circle',   z=-1,  stim=Disc(position=center, radius=circle_radius, color=(0,0,0)))
		self.stimulus('triangle', z=1,   stim=triangle)
		self.stimulus('red',      z=2,   stim=red)
		self.stimulus('green',    z=2,   stim=green)
		self.stimulus('blue',     z=2,   stim=blue)
		self.stimulus('cursor1',  z=3,   stim=Disc(position=center, radius=10, color=(1,1,1), on=False))
		self.stimulus('cursor2',  z=4,   stim=Disc(position=center, radius=8,  color=(0,0,0), on=False))
		self.stimulus('arrow',    z=4.5, stim=arrow)
		self.stimulus('cue',      z=5,   stim=VisualStimuli.Text(text='?', position=center, anchor='center', color=(1,1,1), font_size=50, on=False))
		self.stimulus('fixation', z=4.2, stim=Disc(position=center, radius=5, color=(1,1,1), on=False))
		
		# set up the strings that are going to be presented in the 'cue' stimulus
		self.cuetext = ['relax', 'feet', 'left', 'right']
		
		# load, and silently start, the continuous feedback sounds
		self.sounds = []
		if int(self.params['AudioFeedback']):
			wavmat = self.params['FeedbackWavs']
			for i in range(len(wavmat)):
				wavlist = wavmat[i]
				if len(wavlist) != 1: raise EndUserError, 'FeedbackWavs matrix should have 1 column'
				try: snd = WavTools.player(wavlist[0])
				except IOError: raise EndUserError, 'failed to load "%s"'%wavlist[0]
				self.sounds.append(snd)
				snd.vol = 0
				snd.play(-1)

		# finally, some fancy stuff from AppTools.StateMonitors, for the developer to check
		# that everything's working OK
		if int(self.params['ShowSignalTime']):
			# turn on state monitors iff the packet clock is also turned on
			addstatemonitor(self, 'Running', showtime=True)
			addstatemonitor(self, 'CurrentBlock')
			addstatemonitor(self, 'CurrentTrial')
			addstatemonitor(self, 'TargetClass')
			addstatemonitor(self, 'Learn')
			
			addphasemonitor(self, 'phase', showtime=True)

			m = addstatemonitor(self, 'fs_reg')
			m.func = lambda x: '% 6.1fHz' % x._regfs.get('SamplesPerSecond', 0)
			m.pargs = (self,)
			m = addstatemonitor(self, 'fs_avg')
			m.func = lambda x: '% 6.1fHz' % x.estimated.get('SamplesPerSecond',{}).get('global', 0)
			m.pargs = (self,)
			m = addstatemonitor(self, 'fs_run')
			m.func = lambda x: '% 6.1fHz' % x.estimated.get('SamplesPerSecond',{}).get('running', 0)
			m.pargs = (self,)
			m = addstatemonitor(self, 'fr_run')
			m.func = lambda x: '% 6.1fHz' % x.estimated.get('FramesPerSecond',{}).get('running', 0)
			m.pargs = (self,)
					
		self.distance = lambda a,b: numpy.sqrt((numpy.asarray(a-b)**2).sum(axis=-1))
		self.distance_scaling = (2.0 ** self.bits['DistanceFromCenter'] - 1.0) / self.distance(self.positions['green'], self.positions['red'])
		
	#############################################################
	
	def StartRun(self):
		
		if int(self.params['ShowFixation']):
			self.stimuli['fixation'].on = True
		
	#############################################################
	
	def Phases(self) :
		
		self.phase(next='startcue',   duration=             3000,   name='baseline')
		self.phase(next='gap',        duration=             1000,   name='startcue')
		self.phase(next='imagine1',   duration=              800,   name='gap')
		self.phase(next='imagine2',   duration=             1000,   name='imagine1') # The 'Learn' state won't be set just yet...
		self.phase(next='imagine3',   duration=             4000,   name='imagine2') # Set it now: let's learn from this phase.
		self.phase(next='stopcue',    duration=             5000,   name='imagine3') # Ok, that's enough learning.
		self.phase(next='intertrial', duration=              800,   name='stopcue')
		self.phase(next='baseline',   duration=randint(1000,3000),  name='intertrial')
		
		self.design(start='intertrial', new_trial='baseline', interblock='idle')
			
	#############################################################
	
	def Transition(self, phase):
		
		# record what's going 
		self.states['BaselineOn'] = int(phase in ['baseline'])
		self.states['StartCueOn'] = int(phase in ['startcue'])
		self.states['StopCueOn']  = int(phase in ['stopcue'])
		self.states['Learn']      = int(phase in ['baseline', 'imagine2']) # the signal-processing module will know to learn during these two phases
		self.states['FeedbackOn'] = int(phase in ['imagine1', 'imagine2', 'imagine3'])
		
		self.stimuli['cue'].on = (phase in ['startcue', 'stopcue'])
		self.stimuli['arrow'].on = (phase in ['startcue'])

		if phase == 'baseline':
			self.states['TargetClass'] = 0

		if phase == 'startcue':
			if int(self.params['AlternateTargets']): self.states['TargetClass'] = 1 + self.states['CurrentTrial'] % self.nclasses
			else: self.states['TargetClass'] = randint(1,self.nclasses)
			t = self.states['TargetClass']
			self.stimuli['cue'].text = self.cuetext[t]
			self.stimuli['arrow'].color = map(lambda x:int(x==t), [1,2,3])
			self.stimuli['arrow'].angle = -120*(t - 1)

		if phase == 'stopcue':
			self.stimuli['cue'].text = self.cuetext[0]
		
	#############################################################
	
	def Process(self, sig):
		
		x = sig.mean(axis=1)
		x = numpy.maximum(x, 0.0)
		
		if x.shape[0] == self.nclasses + 1:
			if x.sum(): x /= x.sum()
			x = x[:self.nclasses,:]
			
		strength = max(0.0, min(1.0, x.sum()))
		if x.sum(): x /= x.sum()
		col = strength * x
		pos = strength * x.T * self.p + (1.0 - strength) * self.positions['origin']
		
		vec = (pos - self.positions['origin']).A.ravel()
		vec = vec[0] + 1j * vec[1]
		dist = self.distance(pos,self.p)
		dist = [int(round(self.distance_scaling * x)) for x in dist]
		self.states['DistanceFromCorner1'],self.states['DistanceFromCorner2'],self.states['DistanceFromCorner3'] = dist
		self.states['DistanceFromCenter'] = int(round(self.distance_scaling * abs(vec)))
		deg = int(round(numpy.angle(vec) * 180.0 / numpy.pi))
		if deg < 0: deg += 360
		self.states['Angle'] = deg
		
		
		pos = pos.A.ravel().tolist()
		col = col.A.ravel().tolist()
		
		fdbk = int(self.states['FeedbackOn']) != 0
		if not fdbk: col = (0,0,0)
		
		if int(self.params['CursorFeedback']):
			self.stimuli['cursor1'].on = fdbk
			self.stimuli['cursor2'].on = fdbk
			self.stimuli['cursor1'].position = pos
			self.stimuli['cursor2'].position = pos
		if int(self.params['ColorFeedback']):
			self.stimuli['circle'].color = col
		if int(self.params['AudioFeedback']):
			for i in range(min(len(self.sounds), len(col))):
				self.sounds[i].vol = col[i]
		
	#############################################################
	
	def StopRun(self):
		
		self.states['FeedbackOn'] = 0
		self.stimuli['cue'].on = False
		self.stimuli['arrow'].on = False
		self.stimuli['circle'].color = (0,0,0)
		self.stimuli['cursor1'].on = False
		self.stimuli['cursor1'].position = self.positions['origin'].A.ravel().tolist()
		self.stimuli['cursor2'].on = False
		self.stimuli['cursor2'].position = self.positions['origin'].A.ravel().tolist()
		self.stimuli['fixation'].on = False
		for snd in self.sounds: snd.vol = 0.0
		
#################################################################
#################################################################
