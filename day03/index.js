const fs = require("fs");

let hashmap = {};
for (let i = 1; i <= 26; i++) {
  hashmap[String.fromCharCode(i + 96)] = i;
}

for (let i = 27; i <= 52; i++) {
  hashmap[String.fromCharCode(i + 38)] = i;
}

const input = fs.readFileSync("./input.txt", "utf8");
const split = input.split("\n");

function GetPriority(char) {
  return hashmap[char];
}

function part1() {
  let result = 0;

  split.forEach((rucksack) => {
    const halfIndex = Math.floor(rucksack.length / 2);
    const compartment1 = rucksack.slice(0, halfIndex);
    const compartment2 = rucksack.slice(halfIndex, rucksack.length);

    for (let i = 0; i < compartment1.length; i++) {
      if (compartment2.includes(compartment1[i])) {
        result += GetPriority(compartment1[i]);
        break;
      }
    }
  });

  console.log(result);
}

function part2() {
  let result = 0;

  for (let j = 0; j < split.length; j += 3) {
    const group = split.slice(j, j + 3);

    for (let i = 0; i < group[0].length; i++) {
      if (group[1].includes(group[0][i]) && group[2].includes(group[0][i])) {
        result += GetPriority(group[0][i]);
        break;
      }
    }
  }

  console.log(result);
}

const part = process.env.part || "part1";

if (part === "part1") part1();
else part2();
