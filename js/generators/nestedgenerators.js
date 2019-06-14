function* risingedge(clk) {
    yield 1;
    yield 2;
}

function* driver(clk) {
    yield* risingedge(clk);
    yield 3;
}

x = driver(0);
console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());

