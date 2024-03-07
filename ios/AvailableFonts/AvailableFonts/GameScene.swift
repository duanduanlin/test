//
//  GameScene.swift
//  AvailableFonts
//
//  Created by duan lin ding on 2024/3/6.
//

import SpriteKit

class GameScene: SKScene {
    
    var familyIdx: Int = 0
    
    override init(size: CGSize) {
        super.init(size: size)
        showCurrentFamily()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        familyIdx += 1
        if familyIdx >= UIFont.familyNames.count{
            familyIdx = 0
        }
        showCurrentFamily()
    }
    
    func showCurrentFamily(){
        removeAllChildren()
        
        let familyName = UIFont.familyNames[familyIdx]
        print("Family: \(familyName)")
        
        let fontNames = UIFont.fontNames(forFamilyName: familyName)
        
        for (idx,fontName) in fontNames.enumerated(){
            let label = SKLabelNode(fontNamed: fontName)
            label.text = fontName
            label.position = CGPoint(x: size.width / 2, y: (size.height * (CGFloat(idx + 1))) / (CGFloat(fontNames.count) + 1))
            label.fontSize = 50
            label.verticalAlignmentMode = .center
            addChild(label)
        }
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
