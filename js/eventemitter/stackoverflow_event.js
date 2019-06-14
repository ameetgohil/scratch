const EventEmitter = require('events').EventEmitter;
const util = require('util');

function Task() {
    EventEmitter.call(this);
    this.setMaxListeners(Infinity);

    this.dosomething = () => {
	console.log("do something");
    };
    
    this.run = (iter) => {
	for(i = 0; i < iter; i++) {
	    this.dosomething();
	    this.emit('someevent');
	}
    }

}

util.inherits(Task, EventEmitter);

task = new Task();

async function do_work() {

    console.log("work 1");

    // use a promise to block completion of do_work() function
    // until task event callback has been invoked
    await (new Promise(resolve => {

	task.once('someevent', (props) => {

	    console.log('event happened');

	    // Now that task callback has been invoked, "resolve" the
	    // enclosing promise to allow do_work()'s execution to complete
	    resolve();

	});
    }));
    
    /*await (new Promise(resolve => {
	
	task.once('someevent', (props) => {
	    
	    console.log('event happened');
	    
	    // Now that task callback has been invoked, "resolve" the
	    // enclosing promise to allow do_work()'s execution to complete
	    resolve();
	    
	});
    }));*/
    
    console.log("work 2");
}

/*function do_work() {
  console.log("work 1");
  task.once('someevent', (props) => {
  console.log('event happened');
  });
  console.log("work 2");
  }*/

async function x() {
    do_work();
    task.run(5);
}

x();


