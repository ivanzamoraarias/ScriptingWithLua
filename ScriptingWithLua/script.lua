players = {}
players[0] = {
	Role = "Ardilla",
	Name = "Pilla",
	Ability = "trolldom",
	Level =90
	}

players[1]= {
	Role = "Dino",
	Name = "Pilla",
	Ability = "trolldom",
	Level = 80}

function addSomething( a, b )
	print("LUA called with "..a.." , "..b.." final \n")
	return a+b
end

function getPlayer(index)
	return players[index]
end

