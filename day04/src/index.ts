import * as fs from "fs";
import path from "path";

const input = fs.readFileSync(path.resolve(__dirname, "../input.txt")).toString()


const lines = input.split("\n")

function getIdPairs(line:string){
  const split = line.replace("\r", "").split(",")
  const firstPair = split[0].split("-")
  const secondPair = split[1].split("-")
  
  return{
    Id11: parseInt(firstPair[0]), 
    Id12: parseInt(firstPair[1]), 
    Id21: parseInt(secondPair[0]), 
    Id22: parseInt(secondPair[1])
  }  
}

function part1(){
  let result = 0

  for(let i = 0; i < lines.length; i++){
    const { Id11, Id12, Id21, Id22 } = getIdPairs(lines[i]);

    if(Id11 >= Id21 && Id12 <= Id22){
      result += 1 
    }
    else if(Id21 >= Id11 && Id22 <= Id12){
      result += 1   
    }
  }

  console.log(result)
}

function part2(){
  let result = 0

  for(let i = 0; i < lines.length; i++){
    const { Id11, Id12, Id21, Id22 } = getIdPairs(lines[i]);

    if(Id21 >= Id11 && Id21 <= Id12){
      result += 1
    }
    else if(Id22 >= Id11 && Id22 <= Id12){
      result += 1
    }
    else if(Id11 >= Id21 && Id12 <= Id22){
      result += 1 
    }
    else if(Id21 >= Id11 && Id22 <= Id12){
      result += 1   
    }
  }

  console.log(result)
}

const part: string = process.env.part || "part1";

if (part === "part1") { 
  part1()
} else {
  part2()
}

part2()


