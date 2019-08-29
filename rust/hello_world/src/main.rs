extern crate regex;
use regex::Regex;
    
fn main() {
    let re = Regex::new(r"^\d{4}-\d{2}-\d{2}$").unwrap();
    println!("Did our date {}  match? {}", "2014-01-01", re.is_match("2014-01-01"));
    println!("Did our date {} match? {}", "201-01-01", re.is_match("201-01-01"));
}
