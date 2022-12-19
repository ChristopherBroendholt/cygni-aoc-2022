using System.Text.RegularExpressions;
using System;
//var input = File.ReadLines("input.txt")

internal class Program
{
    private static void Main(string[] args)
    {
        string input = File.ReadAllText("input.txt");
        var part = Environment.GetEnvironmentVariable("part");

        if (part == "PART1")
        {
            Console.WriteLine("PART1");
            Parser<BoxQueue> parser = new(input);
            parser.Parse();
            Stacker<BoxQueue> Stacker = new Stacker<BoxQueue>(parser.Stacks, parser.Moves);
            Stacker.Stack();
        }
        else if (part == "PART2")
        {
            Console.WriteLine("PART2");
            Parser<BoxStack> parser = new(input);
            parser.Parse();
            Stacker<BoxStack> stacker = new Stacker<BoxStack>(parser.Stacks, parser.Moves);
            stacker.Stack();
        }
    }
}

class Parser<T> where T : BoxesInterface, new() {
    private string Input;
    private List<string> Lines;
    public List<Move> Moves { get; set; }
    public List<T> Stacks { get; set; }

    public Parser(string Input)
    {
        this.Input = Input;
        this.Lines = Input.Split("\n").ToList();

        this.Moves = new List<Move>();
        this.Stacks = new List<T>();
    }

    public void Parse(){
        
        int splitIndex = Lines.IndexOf("\r");
        char[] stackNumbers = Lines[splitIndex - 1].ToCharArray();

        for(int j = 0; j < stackNumbers.Count(); j++){
            
            if(Regex.IsMatch(stackNumbers[j].ToString(), "\\d")){
                var boxStack = new T();
                
                for(int i = splitIndex - 2; i >= 0; i--){
                    if(Lines[i].ToCharArray()[j] != ' '){
                        boxStack.AddBox(Lines[i].ToCharArray()[j]);        
                    }
                }

                Stacks.Add(boxStack);
            }
        }

        Lines.Skip(splitIndex + 1).ToList().ForEach((line) => {
            var matches = Regex.Matches(line, "\\d+");

            int amount = Int32.Parse(matches[0].Value);
            int to = Int32.Parse(matches[1].Value);
            int from = Int32.Parse(matches[2].Value);

            Moves.Add(new Move(amount, to, from)); 
        });
    }

}

class Stacker<T> where T : BoxesInterface {

    public List<T> Stacks {get; set;}
    public List<Move> Moves {get; set;}

    public Stacker(List<T> stacks, List<Move> moves){
        this.Stacks = stacks;
        this.Moves = moves;
    }

    public void Stack(){
        
        for(int i = 0; i < Moves.Count(); i++){
            Move move = Moves[i];
            
            var stack = Stacks[move.From - 1].RemoveBoxes(move.Amount);
            Stacks[move.To - 1].AddBoxes(stack);
        }

        for (int i = 0; i < Stacks.Count(); i++)
        {
            Console.Write(Stacks[i].GetTopBox());
        }
    }
}

interface BoxesInterface {
    void Print();

    char GetTopBox();

    void AddBox(char box);

    IEnumerable<char> RemoveBoxes(int amount);

    void AddBoxes(IEnumerable<char> newBoxes);
}

class BoxStack : BoxesInterface {
    
    Stack<char> boxes = new Stack<char>();
    
    public void Print(){
        for(int i = 0; i < boxes.Count(); i++){
            Console.Write(boxes.Reverse().ElementAt(i) + " ");
        }

        Console.WriteLine("");
    }

    public char GetTopBox(){
        return boxes.First();
    }

    public void AddBox(char Box){
        boxes.Push(Box);
    }

    public IEnumerable<char> RemoveBoxes(int amount){
        Stack<char> removedBoxes = new Stack<char>();
        
        for (int i = 0; i < amount; i++)
        {
            removedBoxes.Push(boxes.Pop());
        }

        return removedBoxes;
    }

    public void AddBoxes(IEnumerable<char> newBoxes){
        var newBoxesStack = new Stack<char>(newBoxes);

        while(newBoxesStack.Count != 0){
            boxes.Push(newBoxesStack.Pop());
        }
    }
}

class BoxQueue : BoxesInterface{
    
    Stack<char> boxes = new Stack<char>();
    
    public void Print(){
        for(int i = 0; i < boxes.Count(); i++){
            Console.Write(boxes.Reverse().ElementAt(i) + " ");
        }

        Console.WriteLine("");
    }

    public char GetTopBox(){
        return boxes.First();
    }

    public void AddBox(char Box){
        boxes.Push(Box);
    }

    public IEnumerable<char> RemoveBoxes(int amount){
        Queue<char> removedBoxes = new Queue<char>();
        
        for (int i = 0; i < amount; i++)
        {
            removedBoxes.Enqueue(boxes.Pop());
        }

        return removedBoxes;
    }

    public void AddBoxes(IEnumerable<char> newBoxes){
        var newBoxesQueue = new Queue<char>(newBoxes);

        while(newBoxesQueue.Count != 0){
            boxes.Push(newBoxesQueue.Dequeue());
        }
    }
}

record Move(int Amount, int From, int To);