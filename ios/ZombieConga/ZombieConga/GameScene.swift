import SpriteKit

class GameScene:SKScene{
    //添加背景1作为精灵
    //    let background = SKSpriteNode(imageNamed: "background1")
    //添加一个僵尸
    let zombie = SKSpriteNode(imageNamed: "zombie1")
    //添加时间统计变量
    var lastUpdateTime: TimeInterval = 0
    var dt: TimeInterval = 0
    //移动速度
    let zombieMovePointPerSec: CGFloat = 480.0
    let catMovePointPerSec: CGFloat = 480.0
    //速度向量
    var velocity = CGPoint.zero
    //游戏区域
    let playableRect: CGRect
    //上次触摸位置
    var lastTouchLocation: CGPoint?
    //旋转速度
    let zombieRotateRadiansPerSec:CGFloat = 4.0 * π
    //动画
    let zombieAnimation: SKAction
    //声音
    let catCollisionSound: SKAction = SKAction.playSoundFileNamed("hitCat", waitForCompletion: false)
    let enemyCollisionSound: SKAction = SKAction.playSoundFileNamed("hitCatLady", waitForCompletion: false)
    //受保护状态
    var zombieWasProtected: Bool = false
    //运行状态
    var lives: Int = 5
    var gameOver: Bool = false
    //相机
    let cameraNode = SKCameraNode()
    let cameraMovePointsPerSec: CGFloat = 200.0
    //标签
    let livesLabel = SKLabelNode(fontNamed: "Glimstick")
    
    override init(size: CGSize){
        let maxAspectRatio:CGFloat = 16.0/9.0
        let playableHeight = size.width / maxAspectRatio
        let playableMargin = (size.height - playableHeight) / 2.0
        playableRect = CGRect(x: 0, y: playableMargin, width: size.width, height: playableHeight)
        
        var textures:[SKTexture] = []
        for i in 1...4{
            textures.append(SKTexture(imageNamed: "zombie\(i)"))
        }
        
        textures.append(textures[2])
        textures.append(textures[1])
        zombieAnimation = SKAction.animate(with: textures, timePerFrame: 0.1)
        super.init(size: size)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func didMove(to view: SKView) {
        
        //设置背景音乐
        playBackgroundMusic(filename: "backgroundMusic.mp3")
        //设置背景颜色
        backgroundColor = SKColor.black
        
        for i in 0...1{
            let background = backgroundNode()
            background.anchorPoint = CGPoint.zero
            //设置图片位置为居中显示
            background.position = CGPoint(x: CGFloat(i) * background.size.width, y: 0)
            //将背景图片置于最后
            background.zPosition = -1
            background.name = "background"
            addChild(background)
        }
        
        
        //放置僵尸
        zombie.position = CGPoint(x: 400, y: 400)
        zombie.zPosition = 100
        //添加精灵
        addChild(zombie)
        //        zombie.run(SKAction.repeatForever(zombieAnimation))
        //绘制边框
        //        debugDrawPlayableArea()
        //生成敌人
        run(SKAction.repeatForever(SKAction.sequence([SKAction.run(spawnEnemy),SKAction.wait(forDuration: 4.0)])))
        //生成小猫
        run(SKAction.repeatForever(SKAction.sequence([SKAction.run(spawnCat),SKAction.wait(forDuration: 1.0)])))
        
        //        actionTestByTurtle()
        addChild(cameraNode)
        camera = cameraNode
        setCameraPosition(position: CGPoint(x: size.width/2, y: size.height/2))
        //放置标签
        livesLabel.text = "Lives: \(lives)"
        livesLabel.fontColor = SKColor.black
        livesLabel.fontSize = 100
        livesLabel.zPosition = 100
        livesLabel.position = CGPoint(x: -cameraRect.size.width / 2 + CGFloat(20), y: -cameraRect.size.height / 2 - CGFloat(20) - overlapAmount() / 2)
        livesLabel.horizontalAlignmentMode = .left
        livesLabel.verticalAlignmentMode = .bottom
        cameraNode.addChild(livesLabel)
//        livesLabel.position = CGPoint(x: size.width / 2, y: size.height / 2)
//        addChild(livesLabel)
    }
    
    override func update(_ currentTime: TimeInterval) {
        //计算刷新时间
        if lastUpdateTime > 0{
            dt = currentTime - lastUpdateTime
        }else{
            dt = 0
        }
        lastUpdateTime = currentTime
        //print("\(dt*1000) ms since last update")
        
        //边界检查
        //boundsCheckZombie()
        
        //移动僵尸到触摸点
//        if let stopPoint = lastTouchLocation{
//            if (stopPoint - zombie.position).length() < zombieMovePointPerSec * dt{
//                zombie.position = stopPoint
//                velocity = CGPoint.zero
//                stopZombieAnimation()
//            }else{
//                moveSprite(sprite: zombie, velocity: velocity)
//                rotateSprite(sprite: zombie, direction: velocity, rotateRadiansPerSec: zombieRotateRadiansPerSec)
//            }
//        }
        //碰撞检查
        //        checkCollisions()
        moveTrain()
        //判断结果
        if lives <= 0 && !gameOver{
            backgroundMusicPlayer.stop()
            gameOver = true
            print("you lose!")
            let gameOverScene = GameOverScene(size: size, won: false)
            gameOverScene.scaleMode = scaleMode
            let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
            view?.presentScene(gameOverScene, transition: reveal)
        }
        moveCamera()
        //        cameraNode.position = zombie.position
    }
    
    override func didEvaluateActions() {
        boundsCheckZombie()
        checkCollisions()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else {
            return
        }
        let touchLocation = touch.location(in: self)
        sceneTouched(touchLocation: touchLocation)
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else {
            return
        }
        let touchLocation = touch.location(in: self)
        sceneTouched(touchLocation: touchLocation)
    }
    
    func moveCamera(){
        let backgroundVelocity = CGPoint(x: cameraMovePointsPerSec, y: 0)
        let amountToMove = backgroundVelocity * CGFloat(dt)
        cameraNode.position+=amountToMove
        
        enumerateChildNodes(withName: "background"){node,_ in
            let background = node as! SKSpriteNode
            if background.position.x + background.size.width < self.cameraRect.origin.x{
                background.position = CGPoint(x: background.position.x + background.size.width * 2, y: background.position.y)
            }
        }
    }
    
    var cameraRect: CGRect {
        return CGRect(x: getCameraPosition().x - size.width / 2 + (size.width - playableRect.width) / 2, y: getCameraPosition().y - size.height / 2 + (size.height - playableRect.height) / 2, width: playableRect.width, height: playableRect.height)
    }
    
    func backgroundNode() -> SKSpriteNode {
        let backgroundNode = SKSpriteNode()
        backgroundNode.anchorPoint = CGPoint.zero
        backgroundNode.name = "background"
        
        let background1 = SKSpriteNode(imageNamed: "background1")
        background1.anchorPoint = CGPoint.zero
        background1.position = CGPoint(x: 0, y: 0)
        
        let background2 = SKSpriteNode(imageNamed: "background2")
        background2.anchorPoint = CGPoint.zero
        background2.position = CGPoint(x: background1.size.width, y: 0)
        
        backgroundNode.addChild(background1)
        backgroundNode.addChild(background2)
        backgroundNode.size = CGSize(width: background1.size.width + background2.size.width, height: background1.size.height)
        
        return backgroundNode
    }
    
    func overlapAmount() -> CGFloat{
        guard let view = self.view else {
            return 0
        }
        
        let scale = view.bounds.size.width / self.size.width
        let scaledHeight = self.size.height * scale
        let scaledOverlap = scaledHeight - view.bounds.size.height
        
        return scaledOverlap / scale
    }
    
    func getCameraPosition() -> CGPoint {
        return CGPoint(x: cameraNode.position.x, y: cameraNode.position.y + overlapAmount()/2)
    }
    
    func setCameraPosition(position: CGPoint) {
        cameraNode.position = CGPoint(x: position.x, y: position.y - overlapAmount()/2)
    }
    /// 以指定的速度移动精灵
    /// - Parameters:
    ///   - sprite: 要移动的精灵
    ///   - velocity: 速度
    func moveSprite(sprite: SKSpriteNode, velocity: CGPoint){
        //速度*刷新时间=单帧移动距离
        let amountToMove = velocity * CGFloat(dt)
        //print("Amount to move: \(amountToMove)")
        sprite.position += amountToMove
    }
    
    
    /// 移动精灵到某处
    /// - Parameter location: 目的地
    func moveZombieToward(location: CGPoint){
        let offset = location - zombie.position
        let direction = offset.normalized()
        velocity = direction * zombieMovePointPerSec
        startZombieAnimation()
    }
    
    
    /// 处理触摸
    /// - Parameter touchLocation: 触摸点
    func sceneTouched(touchLocation: CGPoint){
        lastTouchLocation = touchLocation
        moveZombieToward(location: touchLocation)
    }
    
    
    /// 边界检查
    func boundsCheckZombie(){
        let bottmLeft = CGPoint(x: CGRectGetMinX(cameraRect), y: CGRectGetMinY(cameraRect))
        let topRight = CGPoint(x: CGRectGetMaxX(cameraRect), y: CGRectGetMaxY(cameraRect))
        
        if zombie.position.x <= bottmLeft.x{
            zombie.position.x = bottmLeft.x
            velocity.x = -velocity.x
        }
        
        if zombie.position.x >= topRight.x{
            zombie.position.x = topRight.x
            velocity.x = -velocity.x
        }
        
        if zombie.position.y <= bottmLeft.y{
            zombie.position.y = bottmLeft.y
            velocity.y = -velocity.y
        }
        
        if zombie.position.y >= topRight.y {
            zombie.position.y = topRight.y
            velocity.y = -velocity.y
        }
    }
    
    
    /// 绘出安全边界（调试）
    func debugDrawPlayableArea(){
        let shape = SKShapeNode()
        let path = CGMutablePath()
        path.addRect(playableRect)
        
        shape.path = path
        shape.strokeColor = SKColor.red
        shape.lineWidth = 4.0
        addChild(shape)
    }
    
    
    /// 以指定的方向和速度旋转精灵
    /// - Parameters:
    ///   - sprite: 要旋转的精灵
    ///   - direction: 方向
    ///   - rotateRadiansPerSec: 速度
    func rotateSprite(sprite: SKSpriteNode, direction: CGPoint, rotateRadiansPerSec: CGFloat){
        let shortest:CGFloat = shortestAngleBetween(angle1: direction.angle, angle2: sprite.zRotation)
        var amtToRotate:CGFloat = rotateRadiansPerSec * dt
        if abs(shortest) < amtToRotate{
            amtToRotate = shortest
        }
        sprite.zRotation += amtToRotate*amtToRotate.sign()
    }
    
    
    /// 生成敌人
    func spawnEnemy(){
        let enemy = SKSpriteNode(imageNamed: "enemy")
        enemy.name = "enemy"
        enemy.position = CGPoint(x: CGRectGetMinX(cameraRect) + (size.width + enemy.size.width) / 2, y: CGFloat.random(min: CGRectGetMinY(cameraRect) + enemy.size.height / 2, max: CGRectGetMaxY(cameraRect) - enemy.size.height / 2))
        enemy.zPosition = 50
        addChild(enemy)
        
        let actionMove =  SKAction.moveBy(x: -size.width-enemy.size.width*2, y: 0, duration: 4.0)
        let actionRemove = SKAction.removeFromParent()
        
        enemy.run(SKAction.sequence([actionMove,actionRemove]))
    }
    
    func spawnCat(){
        let cat = SKSpriteNode(imageNamed: "cat")
        cat.name = "cat"
        cat.position = CGPoint(x: CGFloat.random(min: CGRectGetMinX(cameraRect), max: CGRectGetMaxX(cameraRect)), y: CGFloat.random(min: CGRectGetMinY(cameraRect), max: CGRectGetMaxY(cameraRect)))
        cat.setScale(0)
        cat.zPosition = 50
        addChild(cat)
        
        //左右摆动
        cat.zRotation = -π / 16.0
        let leftWiggle = SKAction.rotate(byAngle: π / 8.0, duration: 0.5)
        let rightWiggle = leftWiggle.reversed()
        let fullWiggle = SKAction.sequence([leftWiggle,rightWiggle])
        let wiggleWait = SKAction.repeat(fullWiggle, count: 10)
        
        //缩放
        let scaleUp = SKAction.scale(by: 1.2, duration: 0.25)
        let scaleDown = scaleUp.reversed()
        let fullScale = SKAction.sequence([scaleUp,scaleDown,scaleUp,scaleDown])
        
        let scaleAndWiggleWait = SKAction.repeat(SKAction.group([fullScale,fullWiggle]), count: 10)
        
        
        let actionAppear = SKAction.scale(to: 1.0, duration: 0.5)
        let actionWait = SKAction.wait(forDuration: 10.0)
        let actionDisappear = SKAction.scale(to: 0, duration: 0.5)
        let actionRemove = SKAction.removeFromParent()
        cat.run(SKAction.sequence([actionAppear,scaleAndWiggleWait,actionDisappear,actionRemove]))
    }
    /// 开启动画
    func startZombieAnimation(){
        if zombie.action(forKey: "animation") == nil{
            zombie.run(SKAction.repeatForever(zombieAnimation),withKey: "animation")
        }
    }
    
    /// 停止动画
    func stopZombieAnimation(){
        zombie.removeAction(forKey: "animation")
    }
    
    func zombieBlink(){
        zombieWasProtected = true
        let blinkTimes = 10.0
        let duration = 3.0
        let blinkAction = SKAction.customAction(withDuration: duration){node,elapsedTime in
            let slice = duration / blinkTimes
            let reminder = Double(elapsedTime.truncatingRemainder(dividingBy: slice))
            node.isHidden = reminder > slice / 2
        }
        zombie.run(blinkAction){
            self.zombieWasProtected = false
        }
    }
    
    func moveTrain(){
        var trainCount = 0
        var targetPosition = zombie.position
        
        enumerateChildNodes(withName: "train"){node,_ in
            trainCount += 1
            if !node.hasActions(){
                let duration = 0.3
                let offset = targetPosition - node.position
                let direction = offset.normalized()
                let amountToMovePerSec = direction * self.catMovePointPerSec
                let amountToMove = amountToMovePerSec * duration
                let actionMove = SKAction.moveBy(x: amountToMove.x, y: amountToMove.y, duration: duration)
                node.run(actionMove)
            }
            targetPosition = node.position
        }
        if trainCount >= 15 && !gameOver{
            backgroundMusicPlayer.stop()
            gameOver = true
            print("you win")
            let gameOverScene = GameOverScene(size: size, won: true)
            gameOverScene.scaleMode = scaleMode
            let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
            view?.presentScene(gameOverScene, transition: reveal)
        }
    }
    
    func loseCats(){
        var loseCount = 0
        
        enumerateChildNodes(withName: "train"){node, stop in
            var randomSpot: CGPoint = node.position
            randomSpot.x += CGFloat.random(min: -100, max: 100)
            randomSpot.y += CGFloat.random(min: -100, max: 100)
            node.name = ""
            node.run(SKAction.sequence(
                [SKAction.group(
                    [SKAction.rotate(byAngle: π*4, duration: 1.0),
                     SKAction.move(to: randomSpot, duration: 1.0),
                     SKAction.scale(to: 0, duration: 1.0)]
                ),
                 SKAction.removeFromParent()]
            ))
            
            loseCount += 1
            if loseCount >= 2{
                stop.initialize(to: true)
            }
        }
    }
    
    
    func zombieHitCat(cat: SKSpriteNode){
        //        print("zombieHitCat")
        //        cat.removeFromParent()
        cat.removeAllActions()
        cat.setScale(1.0)
        cat.zRotation = 0.0
        cat.name = "train"
        let turnGreen = SKAction.colorize(with: SKColor.green, colorBlendFactor: 1.0, duration: 0.2)
        cat.run(turnGreen)
        run(catCollisionSound)
        //        run(SKAction.playSoundFileNamed("hitCat", waitForCompletion: true))
        //        run(SKAction.playSoundFileNamed("hitCatLady", waitForCompletion: false))
    }
    
    func zombieHitEnemy(enemy: SKSpriteNode){
        //        print("zombieHitEnemy")
        //        enemy.removeFromParent()
        zombieBlink()
        loseCats()
        lives -= 1
        run(enemyCollisionSound)
        //        run(SKAction.playSoundFileNamed("hitCatLady", waitForCompletion: false))
    }
    
    func checkCollisions(){
        var hitCats: [SKSpriteNode] = []
        enumerateChildNodes(withName: "cat"){ node,_ in
            if let cat = node as? SKSpriteNode{
                if cat.frame.intersects(self.zombie.frame){
                    hitCats.append(cat)
                }
            }
        }
        
        for cat in hitCats{
            zombieHitCat(cat: cat)
        }
        
        if !zombieWasProtected{
            var hitEnemys: [SKSpriteNode] = []
            enumerateChildNodes(withName: "enemy"){node,_ in
                if let enemy = node as? SKSpriteNode{
                    if enemy.frame.intersects(self.zombie.frame){
                        hitEnemys.append(enemy)
                    }
                }
            }
            
            for enemy in hitEnemys {
                zombieHitEnemy(enemy: enemy)
            }
        }
    }
    
    func actionTestByTurtle(){
        //乌龟测试
        let turtle = SKSpriteNode(imageNamed: "turtle")
        turtle.position = CGPoint(x: size.width * 5/6, y: size.height / 2)
        addChild(turtle)
        //平移
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.group([
        //                    SKAction.moveTo(x:CGRectGetMaxX(playableRect), duration: 1.0),
        //                    SKAction.moveTo(y:CGRectGetMinY(playableRect), duration: 1.0),
        //                ]),
        //                SKAction.group([
        //                    SKAction.moveTo(x:turtle.position.x, duration: 1.0),
        //                    SKAction.moveTo(y:turtle.position.y, duration: 1.0),
        //                ])
        //              ])
        //            ))
        //旋转
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.rotate(toAngle: π/2, duration: 1.0, shortestUnitArc:true),
        //                SKAction.rotate(toAngle: π, duration: 1.0, shortestUnitArc:true),
        //                SKAction.rotate(toAngle: -π/2, duration: 1.0, shortestUnitArc:true),
        //                SKAction.rotate(toAngle: π, duration: 1.0, shortestUnitArc:true),
        //              ])
        //            ))
        //横行伸缩
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.group([
        //                    SKAction.resize(toWidth: turtle.size.width*2, duration: 1.0),
        //                    SKAction.resize(toHeight: turtle.size.height/2, duration: 1.0)
        //                ]),
        //                SKAction.group([
        //                    SKAction.resize(toWidth: turtle.size.width, duration: 1.0),
        //                    SKAction.resize(toHeight: turtle.size.height, duration: 1.0)
        //                ])
        //              ])
        //            ))
        //横行伸缩
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.group([
        //                    SKAction.scaleX(to: 3.0, duration:1.0),
        //                    SKAction.scaleY(to: 0.5, duration:1.0)
        //                ]),
        //                SKAction.group([
        //                    SKAction.scaleX(to: 1.0, duration:1.0),
        //                    SKAction.scaleY(to: 1.0, duration:1.0)
        //                ])
        //              ])
        //            ))
        //纵向弹跳
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.moveBy(x: 0, y: CGRectGetHeight(playableRect) * 1/6, duration: 0.2),
        //                SKAction.moveBy(x: 0, y: -CGRectGetHeight(playableRect) * 1/6, duration: 0.2)
        //              ])
        //            ))
        //闪烁
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.fadeAlpha(to: 0.25, duration: 0.5),
        //                SKAction.fadeAlpha(to: 1.0, duration: 0.5),
        //              ])
        //            ))
        
        //变色
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.colorize(with: SKColor.red, colorBlendFactor: 1.0, duration: 1.0),
        //                SKAction.colorize(withColorBlendFactor: 0.0, duration: 1.0),
        //                SKAction.colorize(with: SKColor.green, colorBlendFactor: 1.0, duration: 1.0),
        //                SKAction.colorize(withColorBlendFactor: 0.0, duration: 1.0),
        //                SKAction.colorize(with: SKColor.blue, colorBlendFactor: 1.0, duration: 1.0),
        //                SKAction.colorize(withColorBlendFactor: 0.0, duration: 1.0),
        //              ])
        //            ))
        
        //沿轨迹移动
        //        let circle = CGPath(roundedRect: CGRect(x: CGRectGetMinX(playableRect), y: CGRectGetMinY(playableRect), width: 400, height: 400), cornerWidth: 200, cornerHeight: 200, transform: nil)
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.follow(circle, asOffset: false, orientToPath: false, duration: 5.0)
        //              ])
        //            ))
        
        //跳动
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * 1/6, duration: 1.0),
        //                SKAction.wait(forDuration: 2.0, withRange:2.0),
        //                SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * -1/6, duration: 1.0),
        //              ])
        //            ))
        
        //        let queue = DispatchQueue(__label: "com.razeware.actionscatalog.bgqueue", attr: nil)
        //            var workDone = true
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([
        //                SKAction.run({
        //                  if (workDone) {
        //                    workDone = false
        //                      turtle.run(SKAction.rotate(byAngle: π*2, duration:1.0))
        //                      turtle.run(SKAction.run({
        //                      sleep(1)
        //                      workDone = true
        //                    }, queue: queue))
        //                  }
        //                }, queue: queue),
        //                SKAction.wait(forDuration: 1.0)
        //              ])
        //            ))
        
        // "Blink" action
        //        let blinkTimes = 6.0
        //        let duration = 2.0
        //        turtle.run(SKAction.repeatForever(
        //            SKAction.customAction(withDuration: duration) { node, elapsedTime in
        //                let slice = duration / blinkTimes
        //                let remainder = Double(elapsedTime).truncatingRemainder(dividingBy: slice)
        //                node.isHidden = remainder > slice / 2
        //            }
        //        ))
        
        // "Jump" action
        //        let dogStart = turtle.position
        //        let jumpHeight = 100.0
        //        let dogDuration = 2.0
        //        turtle.run(SKAction.repeatForever(
        //            SKAction.customAction(withDuration: dogDuration) { node, elapsedTime in
        //                let fraction = Double(elapsedTime) / dogDuration
        //                let yOff = jumpHeight * 4 * fraction * (1 - fraction)
        //                node.position = CGPoint(x: node.position.x, y: dogStart.y + CGFloat(yOff))
        //            }
        //        ))
        
        //        // "Sin wave"
        //        let turtleStart = turtle.position
        //        let amplitude = 25.0
        //        let turtleDuration = 1.0
        //        let duration = 2.0
        //        turtle.run(SKAction.repeatForever(
        //            SKAction.customAction(withDuration: duration) { node, elapsedTime in
        //                let fraction = Double(elapsedTime) / turtleDuration
        //                let yOff = sin(π * 2 * fraction) * amplitude
        //                node.position = CGPoint(x: node.position.x, y: turtleStart.y + CGFloat(yOff))
        //            }
        //        ))
        
        // SKActionTimingMode.EaseIn
        //        let MoveUp = SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * 1/6, duration: 1.0)
        //        MoveUp.timingMode = .easeIn
        //        let MoveDown = MoveUp.reversed()
        //        turtle.run(SKAction.repeatForever(
        //              SKAction.sequence([MoveUp, MoveDown])
        //            ))
        
        // SKActionTimingMode.EaseIOut
        //        let MoveUpEO = SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * 1/6, duration: 1.0)
        //        let MoveUpEI = SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * 1/6, duration: 1.0)
        //        MoveUpEI.timingMode = .easeIn
        //        MoveUpEO.timingMode = .easeOut
        //        let MoveDownEI = MoveUpEI.reversed()
        //        turtle.run(SKAction.repeatForever(
        //            SKAction.sequence([MoveUpEO, MoveDownEI])
        //        ))
        
        // SKActionTimingMode.EaseInEaseOut
        //        let turtleMoveUp = SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * 1/6, duration: 1.0)
        //        let MoveUpEI = SKAction.moveBy(x: 0, y: CGRectGetHeight(self.playableRect) * 1/6, duration: 1.0)
        //        MoveUpEI.timingMode = .easeIn
        //        turtleMoveUp.timingMode = .easeInEaseOut
        //        let turtleMoveDown = MoveUpEI.reversed()
        //        turtle.run(SKAction.repeatForever(
        //            SKAction.sequence([turtleMoveUp, turtleMoveDown])
        //        ))
        
        //        turtle.run(SKAction.repeatForever(
        //            SKAction.sequence([
        //                SKAction.hide(),
        //                SKAction.wait(forDuration: 0.1),
        //                SKAction.unhide(),
        //                SKAction.wait(forDuration: 0.1),
        //            ])
        //        ))
    }
    
}
