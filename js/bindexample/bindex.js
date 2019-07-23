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
    this.cb();
  }


}




let c = new Consumer({});



let o = {name:'the object', fun:function() { console.log('my name is ' + this.name)}};


// c.setCb(()=>{
//   console.log('cb 1');
// });

// c.setCb(o.fun);
c.setCb(o.fun.bind(o));


c.run();