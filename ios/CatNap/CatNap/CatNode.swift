//
//  CatNode.swift
//  CatNap
//
//  Created by duan lin ding on 2024/4/6.
//

import Foundation
import SpriteKit

class CatNode: SKSpriteNode,CustomNodeEvents {
    func didMoveToScene() {
        print("cat added to scene")
        let catBodyTexture = SKTexture(imageNamed: "cat_body_outline")
        parent!.physicsBody = SKPhysicsBody(texture: catBodyTexture, size: catBodyTexture.size())
        parent!.physicsBody!.categoryBitMask = PhysicsCategory.Cat
        parent!.physicsBody!.collisionBitMask = PhysicsCategory.Block | PhysicsCategory.Edge
        parent!.physicsBody!.contactTestBitMask = PhysicsCategory.Edge | PhysicsCategory.Bed
    }
    
    func wakeUp(){
        for child in children{
            child.removeFromParent()
        }
        
        texture = nil
        color = SKColor.clear
        
        let catAwake = SKSpriteNode(fileNamed: "CatWakeUp")!.childNode(withName: "cat_awake")
        
        catAwake?.move(toParent: self)
        catAwake?.position = CGPoint(x: -30, y: 100)
    }
    
    func curlAt(scenePoint:CGPoint){
        parent!.physicsBody = nil
        for child in children{
            child.removeFromParent()
        }
        
        texture = nil
        color = SKColor.clear
        
        let catCurl = SKSpriteNode(fileNamed: "CatCurl")!.childNode(withName: "cat_curl")!
        catCurl.move(toParent: self)
        catCurl.position = CGPoint(x: -30, y: 100)
        
        var localPoint = parent!.convert(scenePoint, from: scene!)
        localPoint.y += frame.size.height / 3
        
        run(SKAction.group([
            SKAction.move(to: localPoint, duration: 0.66),
            SKAction.rotate(toAngle: 0, duration: 0.5)]))
    }
}
