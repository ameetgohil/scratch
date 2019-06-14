
let clk_val;
let rstf_val;

let clk = (val) => {
    if(val != null)
	clk_val = val;
    return clk_val;
};

let rstf = (val) => {
    if(val != null)
	rstf_val = val;
    return rstf_val;
};

let intf = (args) => {
    console.log(args);
    let keys = Object.keys(args);
    keys.map((e) => {
	console.log(e);
    });
    let handler = {
	get: (target, name) => {
	    console.log("GET target: " + target + " name: " + name);
	    return args[name]();
	    //return getclk();
	},
	set: function(obj, prop, value) {
	    console.log("SET obj: " + obj + " prop: " + prop + " value: " + value);
	    args[prop](value);
	    //return true;
	}
    };

    return new Proxy({}, handler);
};

let top = intf({clk: clk, rstf: rstf});

top.clk = 1;
console.log(top.clk);
top.clk = 2;
console.log(top.clk);
