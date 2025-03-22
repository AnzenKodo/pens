// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract SlotMachine {
    address public owner;
    uint256 public minimumBet = 0.01 ether;
    uint256 public maxBet = 1 ether;
    
    event SpinResult(
        address indexed player,
        uint256 betAmount,
        uint256[3] result,
        uint256 winnings
    );
    
    constructor() {
        owner = msg.sender;
    }
    
    modifier onlyOwner() {
        require(msg.sender == owner, "Only owner can call this function");
        _;
    }
    
    // Simple random number generator (not cryptographically secure)
    function generateRandom(uint256 seed) private view returns (uint256) {
        return uint256(keccak256(abi.encodePacked(
            block.timestamp,
            block.prevrandao,
            seed,
            msg.sender
        )));
    }
    
    function spin() public payable returns (uint256[3] memory) {
        require(msg.value >= minimumBet, "Bet too low");
        require(msg.value <= maxBet, "Bet too high");
        require(address(this).balance >= msg.value * 10, "Insufficient contract balance");
        
        // Generate 3 random numbers (0-9) for the slot reels
        uint256[3] memory result;
        result[0] = generateRandom(1) % 10;
        result[1] = generateRandom(2) % 10;
        result[2] = generateRandom(3) % 10;
        
        uint256 winnings = 0;
        
        // Simple payout rules
        if (result[0] == result[1] && result[1] == result[2]) {
            // Jackpot: three matching numbers
            winnings = msg.value * 10;
        } else if (result[0] == result[1] || result[1] == result[2] || result[0] == result[2]) {
            // Two matching numbers
            winnings = msg.value * 2;
        }
        
        if (winnings > 0) {
            payable(msg.sender).transfer(winnings);
        }
        
        emit SpinResult(msg.sender, msg.value, result, winnings);
        return result;
    }
    
    // Allow owner to deposit funds
    function deposit() public payable onlyOwner {
        require(msg.value > 0, "Must send ETH to deposit");
    }
    
    // Allow owner to withdraw funds
    function withdraw(uint256 amount) public onlyOwner {
        require(amount <= address(this).balance, "Insufficient balance");
        payable(owner).transfer(amount);
    }
    
    // Get contract balance
    function getBalance() public view returns (uint256) {
        return address(this).balance;
    }
}
