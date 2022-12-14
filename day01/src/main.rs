use std::env;
use std::fs;

fn main(){

    let contents = fs::read_to_string("input.txt")
        .expect("Should have been able to read the file");
    
        
    let input:Vec<&str> = contents.lines().collect();
    let mut caloriesPerPerson = Vec::new();

    let mut calories = 0;
    let len = input.len();

    for cal in input {
        if cal == "" {
            caloriesPerPerson.push(calories);
            calories = 0;
        }else{
            let calorie = cal.parse::<i32>().unwrap();
            calories += calorie;
        }
    }

    caloriesPerPerson.push(calories);
    caloriesPerPerson.sort();

    let length = caloriesPerPerson.len();

    let first = caloriesPerPerson[length - 1]; 
    let second = caloriesPerPerson[length - 2];
    let last = caloriesPerPerson[length - 3];
    
    let total = first + second + last;
    
    let part = match env::var("part") {
        Ok(val) => val,
        Err(_e) => "part1".to_string(),
    };

    println!("Rust");
    if part == "part2" {
        println!("{}", total);
    } else {
        println!("{}", first);
    }
}
