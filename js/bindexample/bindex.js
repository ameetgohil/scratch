'use strict';


class Consumer {
  constructor() {
    this.name = "Consumer class";
    this.cb = null;

  }

  // Tx mode always on channel A
  setCb(x) {
    this.cb = x;
  }

  run() {
    this.cb(565);
  }

  setInternal() {
    // if this is defined at this line, any arrow function will use the same this
    this.setCb( (x) => { console.log(x + ' internal: my name is ' + this.name); });
  }

}




let c = new Consumer({});



let o = {name:'the object', fun: (x) => { 
  console.log(x);
  console.log(x + ' my name is ' + this.name)
}
};


// c.setCb(()=>{
//   console.log('cb 1');
// });

// c.setCb(o.fun);
c.cb = o.fun.bind(o);
//c.setInternal();


c.run();