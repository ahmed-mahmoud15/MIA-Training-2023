import os           # to clean the terminal screen while execution
import colorama     # to change colors in printing
from colorama import Fore, Back, Style

class Weapon():
    '''
        Weapon class Has the data of each weapon the villian use as
        its name: (string)
        the Energy: affects who use this weapon (int)
        the Damage: affects the opponent in his health (int)
        Amount: (int) in some cases 100 means infinity
    '''
    def __init__(self,name , energy = 0, damage = 0, amount = 100):
        self.Name = name
        self.Damage = damage
        self.Energy = energy
        self.Amount = amount

    def Decrease_Amount(self):
        self.Amount -= 1

class Shield():
    '''
        Shield class Has the data of each Shield that the opponent use to protect himself as
        its name: (string)
        the Energy: affects who use this weapon (int)
        the Save: represent how mush this shield will reduce  (float)
        Amount: (int) in some cases 100 means infinity
    '''
    def __init__(self,name , energy = 0, save = 0.0, amount = 100):
        self.Name = name
        self.Save = save
        self.Energy = energy
        self.Amount = amount
    
    def Decrease_Amount(self):
        self.Amount -= 1

class Villain():
    '''
        Villain class Has the main data of each Villain as
        his name: (string)
        the Health: will reduce by the weapon (int)
        the Energy: represent his power limits  (int)
        Shield: the same as SAVE in Shield (float) 
    '''
    def __init__(self,name , health = 100, energy = 500, shield = 0.0):
        self.Name = name
        self.Health = health
        self.Energy = energy
        self.Shield = shield

    def attack(self, opponent):
        pass

    def defend(self):
        pass
          
    # Method to print the data of each villain
    def view_stats(self):
        print(f"{self.Name}'s Health = {self.Health} and Energy = {self.Energy} and Shield = {self.Shield}\n\n")
        
class Gru(Villain):
    '''
        Gru is a  subclass from Villain has the same data but diffrent methods and weapons
    '''

    # All weapons and Shields that Gru can use
    Freeze_Gun = Weapon(name = "Freeze Gun", energy = 50, damage = 11)
    Electric_Pord = Weapon(name = "Electric Pord", energy = 88, damage = 18, amount = 5)
    Mega_Magnet = Weapon(name = "Mega Magnet", energy = 92, damage = 10, amount = 3)
    Kalman_Missile = Weapon(name = "Kalman Missile", energy = 120, damage = 20, amount = 1)

    Energy_Projected_BarrierGun = Shield(name = "Energy-Projected BarrierGun", energy = 20, save = 0.4)
    Selective_Permeability = Shield(name = "Selective Permeability", energy = 50, save = 0.9, amount = 2)


    def __init__(self, name = "Gru"):
        super().__init__(name)
        

    # these functions called by the opponent who will get the damage from gru
    def Get_Damaged_By_Weapon(self, opponent: Villain, weapon: Weapon):
        damage = weapon.Damage
        if self.Shield >= 0:
            damage -= self.Shield * weapon.Damage
            self.Shield = 0
    
        self.Health -= damage
        opponent.Energy -= weapon.Energy
        
        if self.Health < 0:
            self.Health = 0

        if opponent.Energy < 0:
            opponent.Energy = 0

    def Get_Damaged_By_Shield(self, shield: Shield):
        self.Energy -= shield.Energy
        

    def attack(self, opponent):
        while True: # infinite loop to chech if the chosen weapon is available or not
            print(f"1. Freeze Gun   amount = {self.Freeze_Gun.Amount}")
            print(f"2. Electric Pord   amount = {self.Electric_Pord.Amount}")
            print(f"3. Mega Magnet   amount = {self.Mega_Magnet.Amount}")
            print(f"4. Kalman Missile   amount = {self.Kalman_Missile.Amount}\n")

            while True: # infinite loop to Validate the chosen number
                weapon = int(input("Choose the Player's Weapon : "))

                if weapon >= 1 and weapon <= 4:
                    break
            
            print("\n")
            if weapon == 1:
                Attack_With_Weapon = (self.Freeze_Gun)
            elif weapon == 2:
                Attack_With_Weapon = (self.Electric_Pord)
            elif weapon == 3:
                Attack_With_Weapon = (self.Mega_Magnet)
            elif weapon == 4:
                Attack_With_Weapon = (self.Kalman_Missile)
            
            if Attack_With_Weapon.Amount != 0:
                break

        Attack_With_Weapon.Decrease_Amount()
        return Attack_With_Weapon

    def defend(self):
        while True: # infinite loop to chech if the chosen Shield is available or not
            print(f"1. Energy-Projected BarrierGun   amount = {self.Energy_Projected_BarrierGun.Amount}")
            print(f"2. Selective Permeability   amount = {self.Selective_Permeability.Amount}\n")

            while True: # infinite loop to Validate the chosen number
                shield = int(input("Choose Other Player's Shield : "))

                if shield >= 1 and shield <= 2:
                    break
            
            print("\n")
            if shield == 1:
                Defend_With_Shield = (self.Energy_Projected_BarrierGun)
            elif shield == 2:
                Defend_With_Shield = (self.Selective_Permeability)
            
            if Defend_With_Shield.Amount != 0:
                break
        
        self.Shield = Defend_With_Shield.Save
        self.Get_Damaged_By_Shield(Defend_With_Shield)
        Defend_With_Shield.Decrease_Amount()

class Vector(Villain):

    '''
        Vector also is a  subclass from Villain has the same data but diffrent methods and weapons
    '''

    # All weapons and Shields that Vector can use
    Laser_Blasters = Weapon(name = "Laser Blasters", energy = 40, damage = 8)
    Plasma_Grenades = Weapon(name = "Plasma Grenades", energy = 56, damage = 13, amount = 8)
    Sonic_Resonance_Cannon = Weapon(name = "Sonic Resonance Cannon", energy = 100, damage = 22, amount = 3)

    Energy_Net_Trap = Shield(name = "Energy Net Trap", energy = 15, save = 0.32)
    Quantum_Deflector = Shield(name = "Quantum Deflector", energy = 40, save = 0.8, amount = 3)

    def __init__(self, name = "Vector"):
        super().__init__(name)

    # these functions called by the opponent who will get the damage from Vector
    def Get_Damaged_By_Weapon(self, opponent: Villain, weapon: Weapon):
        damage = weapon.Damage
        if self.Shield >= 0:
            damage -= self.Shield * weapon.Damage
            self.Shield = 0
    
        self.Health -= damage
        opponent.Energy -= weapon.Energy
        
        if self.Health < 0:
            self.Health = 0

        if opponent.Energy < 0:
            opponent.Energy = 0

    def Get_Damaged_By_Shield(self, shield: Shield):
        self.Energy -= shield.Energy

    def attack(self, opponent: Villain):
        while True: # infinite loop to chech if the chosen weapon is available or not
            print(f"1. Laser Blasters   amount = {self.Laser_Blasters.Amount}")
            print(f"2. Plasma Grenades  amount = {self.Plasma_Grenades.Amount}")
            print(f"3. Sonic Resonance Cannon   amount = {self.Sonic_Resonance_Cannon.Amount}\n")


            while True: # infinite loop to Validate the chosen number
                weapon = int(input("Choose the Player's Weapon : "))

                if weapon >= 1 and weapon <= 3:
                    break
            
            print("\n")
            if weapon == 1:
                Attack_With_Weapon = (self.Laser_Blasters)
            elif weapon == 2:
                Attack_With_Weapon = (self.Plasma_Grenades)
            elif weapon == 3:
                Attack_With_Weapon = (self.Sonic_Resonance_Cannon)

            if Attack_With_Weapon.Amount != 0:
                break
    
        Attack_With_Weapon.Decrease_Amount()
        return Attack_With_Weapon

    def defend(self):
        while True: # infinite loop to chech if the chosen Shield is available or not
            print(f"1. Energy Net Trap  amount = {self.Energy_Net_Trap.Amount}")
            print(f"2. Quantum Deflector    amount = {self.Quantum_Deflector.Amount}\n")

            while True: # infinite loop to Validate the chosen number
                shield = int(input("Choose The other player's Shield : "))

                if shield >= 1 and shield <= 2:
                    break
            
            print("\n")
            if shield == 1:
                Defend_With_Shield = (self.Energy_Net_Trap)
            elif shield == 2:
                Defend_With_Shield = (self.Quantum_Deflector)
            
            if Defend_With_Shield.Amount != 0:
                break
        
        self.Shield = Defend_With_Shield.Save
        self.Get_Damaged_By_Shield(Defend_With_Shield)
        Defend_With_Shield.Decrease_Amount()


'''
    Method to start the game has 2 parametres 
    each of them has value of 0 or 1
    0 for Gru
    1 foe vector

    PlayerOne is the character chosen by the users to play first
    PlayerTwo is the character chosen by the users to play last

    then start the game with an infinite loop breaks only if the health or energy of each player reaches 0
'''
def Simulate_Game(PlayerOne, PlayerTwo):
    if PlayerOne == 1:
        FirstPlayer = Gru()
    else:
        FirstPlayer = Vector()

    if PlayerTwo == 1:
        SecondPlayer = Gru()
    else:
        SecondPlayer = Vector()

    count_round = 1

    while (FirstPlayer.Health > 0 or SecondPlayer.Health > 0) or (FirstPlayer.Energy > 0 or SecondPlayer.Energy > 0):
        if os.name == 'nt': # clean the terminal after each round
            os.system('cls')
        else:
            os.system('clear')

        print(f"\n\nRound {count_round}\n\n")

        FirstPlayer.view_stats()
        SecondPlayer.view_stats()

        print(f"{FirstPlayer.Name}'s Turn : ")
    
        firstWeapon = FirstPlayer.attack(SecondPlayer)
        SecondPlayer.defend()

        if firstWeapon.Name == "Kalman Missile": # you can't avoid Kalman missle 
            SecondPlayer.Shield = 0

        SecondPlayer.Get_Damaged_By_Weapon(FirstPlayer,firstWeapon)

        # showing the stats of the game after the first player finished his attack
        SecondPlayer.view_stats()
        FirstPlayer.view_stats()

        if SecondPlayer.Health == 0 or SecondPlayer.Energy == 0 or FirstPlayer.Energy == 0:
            break

        print(f"{SecondPlayer.Name}'s Turn : ")
        secondWeapon = SecondPlayer.attack(FirstPlayer)
        FirstPlayer.defend()

        if firstWeapon.Name == "Kalman Missile": # you can't avoid Kalman missle
            SecondPlayer.Shield = 0

        FirstPlayer.Get_Damaged_By_Weapon(SecondPlayer,secondWeapon)

        count_round += 1
    
    if( FirstPlayer.Health == 0 or FirstPlayer.Energy == 0):
        print(Fore.GREEN + f"{SecondPlayer.Name} Wins")
    else:
        print(Fore.GREEN + f"{FirstPlayer.Name} Wins")



print(Fore.RED + f"Sky Clash\n\n" + Style.RESET_ALL)

print(Fore.YELLOW + f"1. GRU")
print(f"2. Vector" + Style.RESET_ALL)

while True:
    playerOne = input("Choose The number of the Player One's Character : ")
    playerOne = int(playerOne)
    if playerOne == 1 or playerOne == 2:
        break

print("\n")

while True:
    playerTwo = input("Choose The number of the Player Two's Character : ")
    playerTwo = int(playerTwo)
    if playerTwo == 1 or playerTwo == 2:
        break

Simulate_Game(playerOne, playerTwo)