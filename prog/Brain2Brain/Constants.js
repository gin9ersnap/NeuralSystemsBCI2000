/**
 * How long each trial should take
 */
var TRIAL_TIME = 6000.0; // Milliseconds

/**
 * How long the countdown lasts
 */
var COUNTDOWN_TIME = 2000; // Milliseconds

/**
 * How long the pause is between a trial ending and the countdown beginning
 */
var PAUSE_BETWEEN_TRIALS = 1000; // Milliseconds

/**
 * How frequently should the game poll the server for a status update?
 */
var POLL_INTERVAL = 250; // Milliseconds

/**
 * Trial types
 */
var AIRPLANE = 'AIRPLANE';
var MISSILE = 'MISSILE';
var TRIAL_TYPE_ENUM = [AIRPLANE, MISSILE];

/**
 * TMS port
 */
var TMS_PORT = 25000;
