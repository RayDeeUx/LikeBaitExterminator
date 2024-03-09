#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/DailyLevelNode.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include <regex>

using namespace geode::prelude;

int dailyLevelID = -1;
int currentLevelID = -1;

const std::regex likebaitComment("(?:(?:[\\S ]+)?(?:here.before|i.?.(?:[\\S ]+)?hack(?:ed)?.(?:this.?comment|my)|(?:(?:\\d?.?)?li?(?:ek|ke)s?\\W?\\W?(?:\\d|if|si|,|=|d|button|this.(?:comment|if)|for|to))|(?:can.i|if.this).?(?:gets?.)?(?:\\d|top)|claim.?your(?:[\\S ]+)?ticket|this.comment.is(?:.not)?.hack(?:ed)?|(?:enough|every.\\d+(?:[\\S ]+)?).li?(?:ek|ke)s?|(?:pl[sz]|get).(?:[\\S ]+)?\\d+.li?(?:ek|ke)s?|this.comment.+li?(?:ek|ke)s?|li?(?:ek|ke)s?(?:[\\S]+)?.(?:or|and).i?|for.(?:[\\S ]+).li?(?:ek|ke)s?|pl[sz].li?(?:ek|ke)s?|i.li?(?:ek|ke)s?.li?(?:ek|ke)s?.?s|if.u.li?(?:ek|ke)s?)(?:[\\S ]+)?|^li?(?:ek|ke)s?.(?:this.)(?:[\\S ]+)?|^(?=if.(?:yo)?u.li?(?:ek|ke)s?.this.then.you(?:.?re?|(?:[\\S ]+)?(?:money|dollars|get|\\$))|i.want.(?:yo)?u(?:[\\S ]+)?li?(?:ek|ke)s?.this)|(?:this.is(?:.an?)?)?.(?:un)?hacked.comment|(?:pl(?:s|z|ease?).)?li?(?:ek|ke)s?(?:.this)?(?:.comment)?.so|gi(?:v|m+i?)e.m(?:ai|y).li?(?:ek|ke)s?|li?(?:ek|ke).my.comment|pass:?.\\d+.li?(?:ek|ke)s?.?(?:pl(?:s|z|ease?)?|so)|(?:[\\S ]+)?comentario(?:[\\S ]+)?hackeado(?:[\\S ]+)?li?(?:ek|ke)s?(?:.infini?tos)?|if.this.gets.li?(?:ek|ke)s?|(?:\\d+).li?(?:ek|ke)s?|unhacked.com+ent|pass.is.\\d+.(?:li?(?:ek|ke)s?|(?:pl(?:s|z|ease?)?|so)))(?:[\\S ]+)?(?:(?!level|and|\\&).)*$", std::regex_constants::icase);

class $modify(CommentCell) {
	void loadFromComment(GJComment* p0) {
		auto comment = p0->m_commentString;
		if ((dailyLevelID != currentLevelID) && Mod::get()->getSettingValue<bool>("onlyOnDaily") && Mod::get()->getSettingValue<bool>("enabled")) {
			CommentCell::loadFromComment(p0);
			return;
		}
		if (Mod::get()->getSettingValue<bool>("enabled") && (std::regex_match(std::string(comment), likebaitComment)) && p0->m_userID != 16) {
			if (Mod::get()->getSettingValue<bool>("markAsSpam")) p0->m_isSpam = true;
			p0->m_likeCount = (p0->m_likeCount) * -10;
			p0->m_commentString = Mod::get()->getSettingValue<std::string>("replacementText");
		}
		CommentCell::loadFromComment(p0);
	}
};

class $modify(DailyLevelNode) {
	bool init(GJGameLevel* p0, DailyLevelPage* p1, bool p2) {
		if (!DailyLevelNode::init(p0, p1, p2)) return false;
		if (!p0) return true;
		dailyLevelID = p0->m_levelID.value();
		return true;
	}
};

class $modify(InfoLayer) {
	bool init(GJGameLevel* level, GJUserScore* score, GJLevelList* list) {
		if (!InfoLayer::init(level, score, list)) return false;
		if (!level) return true;
        #ifdef GEODE_IS_MACOS
        	currentLevelID = level->levelId;
		#else
			currentLevelID = level->m_levelID.value();
		#endif
		return true;
	}
};