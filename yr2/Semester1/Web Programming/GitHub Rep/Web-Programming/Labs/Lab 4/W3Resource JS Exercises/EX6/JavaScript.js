function leapYear(){
    //for condition to be met, year%4/100/400 === 0, thus the conditional ternary operator checks the middle condition, then one of the other
    return (year % 100 === 0) ? (year % 400 === 0) : (year % 4 ===0)
};

console.log(leapYear(2023));
console.log(leapYear(2022));
console.log(leapYear(2020));
console.log(leapYear(2000));
console.log(leapYear(1800));
console.log(leapYear(1600));