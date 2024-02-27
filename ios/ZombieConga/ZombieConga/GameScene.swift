import SpriteKit

class GameScene:SKScene{
    override func didMove(to view: SKView) {
        //设置背景颜色
        backgroundColor = SKColor.black
        //添加背景1作为精灵
        let background = SKSpriteNode(imageNamed: "background1")
        //设置图片位置为居中显示
        background.position = CGPoint(x: size.width/2, y: size.height/2)
        //或者设置精灵的锚点
//        background.anchorPoint = CGPoint.zero
//        background.position = CGPoint.zero
        //尝试旋转精灵
//        background.zRotation = CGFloat(Double.pi) / 8
        //添加精灵
        addChild(background)
        let mysize = background.size
        print("size:\(mysize)")
    }
}
