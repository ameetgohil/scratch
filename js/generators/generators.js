function * foo(x) {
    while(true) {
	x = x * 2;
	yield x;
	yield 1234;
    }
}

var g = foo(2);
console.log(g.next());
console.log(g.next());
console.log(g.next());
