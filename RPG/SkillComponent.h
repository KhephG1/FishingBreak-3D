#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

enum Skills {HEALTH = 0,ATTACK,ACCURACY, ENDURANCE };
class SkillComponent
{
private:
	class Skill {
	private:
		int type;
		int level;
		int exp;
		int expNext;
		int levelCap;

	public:
		Skill(int the_type) {
			type = the_type;
			level = 1;
			exp = 0;
			expNext = 100;
			levelCap = 99;
		}
		virtual ~Skill() {}
		//accessors
		const int& getType() const { return type; }
		const int& getLevel() const { return level; }
		const int& getExp() const { return exp; }
		const int& getExpNext() const { return exp; }
		//Modifiers
		void gainExp(const int amount) {
			exp += amount;
			updateLevel(true);
		}
		void loseExp() {

		}
		void setLevel(const int lvl) { level = lvl; }
		void setLevelCap(const int lvlcap) { levelCap = lvlcap; }
		//functions
		void updateLevel(const bool up) {

			/*
			* increases or decreases the skill level
			*
			* Param: bool up (level increased if true and decreased if false
			* Returns: void
			*/
			if (up) {
				if (level < levelCap) {
					while (exp >= expNext) {
						if (level >= levelCap)
							break;
						++level;
						expNext = level * 100 + level * 3;
					}
				}
			}
			else {
				if (level > 0) {
					while (exp < 0) {
						--level;
						expNext = level * 100 + level * 3;
					}
				}
			}
		}
		void update() {

		}
	};

	std::vector<Skill> skills;
public:
	SkillComponent();
	virtual ~SkillComponent();
	//accessors
	//functions

	int getSkill(const int skill);
	const void gainExp(const int skill, const int exp);
};

#endif