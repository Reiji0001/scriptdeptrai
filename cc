local library = loadstring(game:HttpGet("https://raw.githubusercontent.com/zxciaz/VenyxUI/main/Reuploaded"))()
local venyx = library.new("Venyx", 5013109572)

_G.Settings = {}

getgenv().Load = function()
    print("Loaded!")
	if readfile and writefile and isfile and isfolder then
		if not isfolder("badtimedepzai") then
			makefolder("badtimedepzai")
		end
		if not isfolder("badtimedepzai/gamerac/") then
			makefolder("badtimedepzai/gamerac/")
		end
		if not isfile("badtimedepzai/gamerac/US_" .. game.Players.LocalPlayer.Name .. ".json") then
			writefile("badtimedepzai/gamerac/US_" .. game.Players.LocalPlayer.Name .. ".json", game:GetService("HttpService"):JSONEncode(_G.Settings))
		else
			local Decode = game:GetService("HttpService"):JSONDecode(readfile("badtimedepzai/gamerac/US_" .. game.Players.LocalPlayer.Name .. ".json"))
			for i,v in pairs(Decode) do
				_G.Settings[i] = v
			end
		end
	else
		return warn("Status : Undetected Executor")
	end
end

getgenv().SaveSetting = function()
    print("Save!")
	if readfile and writefile and isfile and isfolder then
		if not isfile("badtimedepzai/gamerac/US_" .. game.Players.LocalPlayer.Name .. ".json") then
			getgenv().Load()
		else
			local Decode = game:GetService("HttpService"):JSONDecode(readfile("badtimedepzai/gamerac/US_" .. game.Players.LocalPlayer.Name .. ".json"))
			local Array = {}
			for i,v in pairs(_G.Settings) do
				Array[i] = v
			end
			writefile("badtimedepzai/gamerac/US_" .. game.Players.LocalPlayer.Name .. ".json", game:GetService("HttpService"):JSONEncode(Array))
		end
	else
		return warn("Status : Undetected Executor")
	end
end

getgenv().Load()

local themes = {
    Background = Color3.fromRGB(24, 24, 24),
    Glow = Color3.fromRGB(0, 0, 0),
    Accent = Color3.fromRGB(10, 10, 10),
    LightContrast = Color3.fromRGB(20, 20, 20),
    DarkContrast = Color3.fromRGB(14, 14, 14),  
    TextColor = Color3.fromRGB(255, 255, 255)
}

local page = venyx:addPage("Test", 5012544693)
local section1 = page:addSection("Section 1")

section1:addDropdown("Chọn cái muốn đổi màu", {"Bàn Tay", "Hiệu Ứng"}, function(value)
    if value == "Bàn Tay" then
        _G.Settings["dang_chon"] = "Handle"
    else
        _G.Settings["dang_chon"] = "Particle"
    end
    getgenv().SaveSetting()
end)

section1:addColorPicker("ColorPicker", (_G.Settings["Handle"]) and _G.Settings["Handle"] or Color3.fromRGB(50, 50, 50), function(color3)
    if _G.Settings["dang_chon"] == "Handle" then
        _G.Settings["Handle"] = color3
    else
        _G.Settings["ColorSequenceKeypoint1"] = color3
    end
    getgenv().SaveSetting()
end)
section1:addColorPicker("ColorPicker2", (_G.Settings["Handle"]) and _G.Settings["Handle"] or Color3.fromRGB(50, 50, 50), function(color3fewfew)
    if _G.Settings["dang_chon"] == "Handle" then
        _G.Settings["Handle"] = color3fewfew
    else
        _G.Settings["ColorSequenceKeypoint12"] = color3fewfew
    end
    getgenv().SaveSetting()
end)

section1:addToggle("doi mau", nil, function(value)
    _G.Settings["doimau"] = value
    spawn(function()
        pcall(function()
            while _G.Settings["doimau"] do wait(.1)
                for i,v in pairs(game.Players.LocalPlayer.Character:GetChildren()) do
                    if v.Name:find("lai") and v:IsA("Tool") then
                        if _G.Settings["Handle"] then
                            v:FindFirstChild("MeshPart").Color = _G.Settings["Handle"]
                            v.MeshPart:FindFirstChild("PointLight").Color = _G.Settings["Handle"]
                        end

                        if _G.Settings["ColorSequenceKeypoint12"] and _G.Settings["ColorSequenceKeypoint1"] then
                            for index,value in pairs(v.MeshPart:GetDescendants()) do
                                if value:IsA("ParticleEmitter") then
                                    local colorSequence = ColorSequence.new({
                                        ColorSequenceKeypoint.new(0, _G.Settings["ColorSequenceKeypoint1"]),
                                        ColorSequenceKeypoint.new(1, _G.Settings["ColorSequenceKeypoint12"])
                                    })
                                    value.Color = colorSequence
                                end
                            end
                        end
                    end
                end
            end
        end)
    end)
end)

section1:addKeybind("Toggle Keybind", Enum.KeyCode.LeftAlt, function()
print("Activated Keybind")
venyx:toggle()
end, function()
print("Changed Keybind")
end)
venyx:SelectPage(venyx.pages[1], true)
-- load
venyx:SelectPage(venyx.pages[1], true)
