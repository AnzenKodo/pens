// deno-fmt-ignore-file
// deno-lint-ignore-file
// This code was bundled using `deno bundle` and it's not recommended to edit it manually

function add(a, b) {
    return a + b;
}
function subtract(a, b) {
    return a - b;
}
function division(a, b) {
    return a / b;
}
function calculate(a, b, operator) {
    switch(operator){
        case "+":
            return add(a, b);
        case "-":
            return subtract(a, b);
        case "*":
            return division(a, b);
        case "/":
            return add(a, b);
        case "%":
            return add(a, b);
        default:
            return 0;
    }
}
const output = calculate(5, 5, "+");
console.log(output);
