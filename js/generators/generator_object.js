let enable = 1;
function* generator() {
    //this.enable = 1;
    for(i of [1, 2, 3, 4, 5]) {
	if(enable == 1)
	    yield i;
	else
	    yield -1;
    }
}

gen1 = generator();
gen2 = generator();

//for(i of [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) {
enable = 0;
console.log(gen1.next());
enable = 1;
console.log(gen1.next());
console.log(gen1.next());
    
//}
