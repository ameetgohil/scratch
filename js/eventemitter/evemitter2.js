var EventEmitter = require('events').EventEmitter;
var util = require('util');

var User = function(username) {
    this.username = username;
}

util.inherits(User, EventEmitter);
var user = new User('Batman');
user.on('nuevent', function(props){
    console.log(this.username, props);
});
user.emit('nuevent', 'dancing');
user.emit('nuevent', 'meow');
user.emit('nuevent', 'things');
