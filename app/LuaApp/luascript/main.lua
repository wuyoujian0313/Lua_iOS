--local wColor = objc.class('UIColor'):whiteColor()
--local cgColor = objc.wrap(wColor).CGColor


function add(a,b)
   return a + b
end

-- 加载Lua脚本时，就会执行
-- print('c_add的结果：'..c_add(3,4))

function dump(tb1)
    for k,v in pairs(tab1) do
        print(k,v)
    end
end

k = {}

r_k = objc.mkref(k) -- for button action

function addButton(vc)
    local blueColor = objc.class('UIColor'):blueColor()
    local whiteColor = objc.class('UIColor'):whiteColor()
    
    local btn = objc.class('UIButton'):buttonWithType(1)
    btn.frame = objc.cgrect(40,200,100,50)
    btn.backgroundColor = objc.class('UIColor'):blueColor()
    btn:setTitleColor_forState(whiteColor, 0)
    btn:setTitle_forState('btn0', 0)
    btn:addTarget_action_forControlEvents(r_k, 'buttonDidPress', 2^6)
    btn:setClipsToBounds(true)
    btn.layer:setCornerRadius(25.0)
    
    function getCGColor(color)
        print("1111")
        local cgColor = color:CGColor()
        return cgColor
    end
    
    local status,cgColor = pcall(getCGColor,whiteColor)
    if(status and cgColor ~= nil) then
       print("22222")
       btn.layer:setBorderColor(cgColor)
    end
    
    btn:setBackgroundImage_forState(objc.class('UIImage'):imageNamed("hot"),0)
    btn.layer:setBorderWidth(0.5)
    vc.view:addSubview(btn)
    
    local btn1 = objc.class('UIButton'):buttonWithType(1)
    btn1.frame = objc.cgrect(40,300,100,50)
    btn1.backgroundColor = objc.class('UIColor'):blueColor()
    btn1:setTitleColor_forState(whiteColor, 0)
    btn1:setTitle_forState('btn1', 0)
    btn1:addTarget_action_forControlEvents(r_k, 'buttonDidPress1', 2^6)
    btn1:setClipsToBounds(true)
    btn1.layer:setCornerRadius(10.0)
    vc.view:addSubview(btn1)

    objc.sweep(btn)
    objc.sweep(btn1)
    
    objc.sweep(v.view)
end

k.buttonDidPress = function()
    print('点击按钮0了!')
end

k.buttonDidPress1 = function()
    print('点击按钮1了!')
end
