function add(a:number, b:number):number
{
    return a+b;
}

function subtract(a:number, b:number):number
{
    return a-b;
}

function multiply(a:number, b:number):number
{
    return a*b;
}

function division(a:number, b:number):number
{
    return a/b;
}

function mod(a:number, b:number):number
{
    return a%b;
}

function calculate(a:number, b:number, operator: string):number
{
    switch(operator)
    {
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

const output = calculate(5,5,"+");
console.log(output);
