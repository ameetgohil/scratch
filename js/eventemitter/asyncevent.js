var events = require("events");

var event = new events.EventEmitter();


event.on("work", function () {

    for (var i = 0; i <= 10; i++) {
        console.log("I do my work " + i);
    }

    event.emit("done");
});

var async = function (cb) {

    event.on("done", cb);
    process.nextTick (function () {         //<-----
        event.emit("work");
    });                                     //<-----
    for (var i = 0; i <= 10; i++) {
        console.log("Async " + i);
    }
}


async(function () {
    console.log("I am done callback!");
});

