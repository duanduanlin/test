//
//  BlockNode.swift
//  CatNap
//
//  Created by duan lin ding on 2024/4/6.
//

import Foundation
import SpriteKit

class BlockNode: SKSpriteNode,CustomNodeEvents,InteractiveNode {
    func interact() {
        isUserInteractionEnabled = false
        run(SKAction.sequence([SKAction.playSoundFileNamed("pop.mp3", waitForCompletion: false),
                               SKAction.scale(to: 0.8, duration: 0.1),
                               SKAction.removeFromParent()
                              ]))
    }
    
    func didMoveToScene() {
        isUserInteractionEnabled = true
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        super.touchesEnded(touches, with: event)
        print("destory block")
        interact()
    }
}
