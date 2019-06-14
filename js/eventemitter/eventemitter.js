console.log("event emitter test");
var events = require('events').EventEmitter;
var emitter = new events.EventEmitter();

emitter.on('newEvent', function (user) {
    console.log(user);
});

emitter.emit('newEvent', 'Batman');
