//
//  MessageNode.swift
//  CatNap
//
//  Created by duan lin ding on 2024/4/7.
//

import Foundation

import SpriteKit

class MessageNode: SKLabelNode {
    var bounceCount:Int = 0
    
    convenience init(message: String) {
        self.init(fontNamed: "AvenirNext-Regular")
        
        text = message
        fontSize = 256.0
        fontColor = SKColor.gray
        zPosition = 100
        
        let front = SKLabelNode(fontNamed: "AvenirNext-Regular")
        front.text = message
        front.fontSize = 256.0
        front.fontColor = SKColor.white
        front.position = CGPoint(x: -2, y: -2)
        addChild(front)
        
        physicsBody = SKPhysicsBody(circleOfRadius: 10)
        physicsBody!.collisionBitMask = PhysicsCategory.Edge
        physicsBody!.categoryBitMask = PhysicsCategory.Label
        physicsBody!.contactTestBitMask = PhysicsCategory.Edge
        physicsBody!.restitution = 0.7
    }
    
    func didBounce()
    {
//        print(bounceCount)
        if bounceCount >= 4{
            removeFromParent()
        }else{
            bounceCount+=1
        }
    }
}
