import SpriteKit

protocol CustomNodeEvents{
    func didMoveToScene()
}

protocol InteractiveNode{
    func interact()
}

struct PhysicsCategory{
    static let None: UInt32 = 0
    static let Cat: UInt32 = 0b1
    static let Block: UInt32 = 0b10
    static let Bed: UInt32 = 0b100
    static let Edge: UInt32 = 0b1000
    static let Label: UInt32 = 0b10000
}

class GameScene: SKScene, SKPhysicsContactDelegate {
    var bedNode:BedNode!
    var catNode:CatNode!
    var playable = true
    
    override func didMove(to view: SKView) {
        let maxAspectRatio:CGFloat = 16.0/9.0
        let maxAspectRatioHeight = size.width / maxAspectRatio
        let playableMargin:CGFloat = (size.height - maxAspectRatioHeight) / 2
        
        let playableRect = CGRect(x: 0, y: playableMargin-20, width: size.width, height: size.height - playableMargin * 2)
        
        physicsBody = SKPhysicsBody(edgeLoopFrom: playableRect)
        physicsWorld.contactDelegate = self
        physicsBody!.categoryBitMask = PhysicsCategory.Edge
        
        enumerateChildNodes(withName: "//*", using: {node,_ in
            if let customNode = node as? CustomNodeEvents{
                customNode.didMoveToScene()
            }
        })
        
        bedNode = childNode(withName: "bed") as? BedNode
        catNode = childNode(withName: "//cat_body") as? CatNode
        
        SKTAudio.sharedInstance().playBackgroundMusic(filename: "backgroundMusic.mp3")
//        bedNode.setScale(1.5)
//        catNode.setScale(1.5)
    }
    
    override func didSimulatePhysics() {
        if playable{
            if abs(catNode.parent!.zRotation) > CGFloat(25).degreesToRadians(){
                lose()
            }
        }
    }
    
    func didBegin(_ contact: SKPhysicsContact) {
        let collision = contact.bodyA.categoryBitMask | contact.bodyB.categoryBitMask
        if collision == PhysicsCategory.Label | PhysicsCategory.Edge{
//            print("label ccollision with edge")
            let labelNode = (contact.bodyA.categoryBitMask == PhysicsCategory.Label) ? contact.bodyA.node : contact.bodyB.node
            
            if let messageNode = labelNode as? MessageNode{
                messageNode.didBounce()
            }
        }
        
        if !playable {
            return
        }
        
        if collision == PhysicsCategory.Cat | PhysicsCategory.Bed{
            print("success")
            win()
        }else if collision == PhysicsCategory.Cat | PhysicsCategory.Edge{
            print("failed")
            lose()
        }
    }
    
    func inGameMessage(text:String){
        let message = MessageNode(message: text)
        message.position = CGPoint(x: CGRectGetMidX(frame), y: CGRectGetMidY(frame))
        addChild(message)
    }
    
    @objc func newGame(){
        let scene = GameScene(fileNamed: "GameScene")
        scene!.scaleMode = scaleMode
        view!.presentScene(scene)
    }
    
    func lose(){
        playable = false
        SKTAudio.sharedInstance().pauseBackgroundMusic()
        run(SKAction.playSoundFileNamed("lose.mp3", waitForCompletion: false))
        
        inGameMessage(text: "Try again...")
        catNode.wakeUp()
        perform(#selector(newGame), with: nil, afterDelay: 5)
        
    }
    
    func win(){
        playable = false
        
        SKTAudio.sharedInstance().pauseBackgroundMusic()
        
        run(SKAction.playSoundFileNamed("win.mp3", waitForCompletion: false))
        
        inGameMessage(text: "Nice job!")
        catNode.curlAt(scenePoint: bedNode.position)
        perform(#selector(newGame), with: nil, afterDelay: 3)
        
    }
}
