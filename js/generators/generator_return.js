function* foo(x) {
  console.log("generator");
  //x = 1;
  for(let i of [0,1,2,3,4]) {
	x = x * 2;
	yield x;
  }
  return 'generator return';
}

var g = foo(2);
console.log('not next');
console.log(g.next());
console.log(g.next());
console.log(g.next());
console.log(g.next());
console.log(g.next());
console.log(g.next());
