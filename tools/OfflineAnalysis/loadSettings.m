function settings = loadSettings()
settings = load('settings.mat');
settings = settings.settings;

%see if this is the first time this function is being called
initFile = fullfile(cd, 'settings.ini');
if exist(initFile, 'file') == 0
  %this is the first time this is being called
  %remove some of the fields in settings left over from dev.
  acceptedFields = {...
    'lstElecsStrFormat', 'coordStrFormat', 'markerColor', 'selectedMarkerColor', 'escKeyButtonCode', 'leftMouseButtonCode', 'headRadius', 'strCleanUpRegexrep', 'defaultElecLabel', 'markerWidth', 'markerHeight', 'markerTextHorzAlign', 'markerTextVerAlign', 'markerTextColor', 'markerTextFontSize', 'headFillColor', 'headOutlineColor', 'headOutlineWidth', 'lstElecsStrFormatLocked', 'labelMaxLen', 'labelPadChar', 'markerWidthECoG', 'markerHeightECoG', 'maxFreqEEG', 'maxFreqECoG', 'hpCutoff', 'spectralStep', 'spectralSize', 'freqBinWidth', 'trend', 'minTrialsPerCondErr', 'minTrialsPerCondWarn', 'pltSelFeatures', 'pltSelSpectra', 'pltSelTopos', 'pltSelTimeSeq', 'dataSegLength', 'freqCondition1', 'freqCondition2', 'freqConditionLabel1', 'freqConditionLabel2', 'p300Condition1', 'p300Condition2', 'p300ConditionLabel1', 'p300ConditionLabel2', 'freqTrialChangeCond', 'p300TrialChangeCond', 'elecs1020', 'ecogCoordRange' ... 
  };

  params2Del = setdiff(fieldnames(settings), acceptedFields);
  settings = rmfield(settings, params2Del);

  save('settings.mat', 'settings');

  %now create the file to indicate that we have performed initialization
  fclose(fopen(initFile, 'w'));
end
