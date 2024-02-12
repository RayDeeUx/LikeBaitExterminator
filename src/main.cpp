#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <regex>

using namespace geode::prelude;

const std::regex likebaitComment("(?:(?:[\\S ]+)?(?:here.before|i.?.(?:[\\S ]+)?hack(?:ed)?.(?:this.?comment|my)|(?:(?:\\d?.?)?li?(?:ek|ke)s?\\W?\\W?(?:\\d|if|si|,|=|d|button|this.(?:comment|if)|for|to))|(?:can.i|if.this).?(?:gets?.)?(?:\\d|top)|claim.?your(?:[\\S ]+)?ticket|this.comment.is(?:.not)?.hack(?:ed)?|(?:enough|every.\\d+(?:[\\S ]+)?).li?(?:ek|ke)s?|(?:pl[sz]|get).(?:[\\S ]+)?\\d+.li?(?:ek|ke)s?|this.comment.+li?(?:ek|ke)s?|li?(?:ek|ke)s?(?:[\\S]+)?.(?:or|and).i?|for.(?:[\\S ]+).li?(?:ek|ke)s?|pl[sz].li?(?:ek|ke)s?|i.li?(?:ek|ke)s?.li?(?:ek|ke)s?.?s|if.u.li?(?:ek|ke)s?)(?:[\\S ]+)?|^li?(?:ek|ke)s?.(?:this.)(?:[\\S ]+)?|^(?=if.(?:yo)?u.li?(?:ek|ke)s?.this(?:[\\S ]+)?you(?:.?re?|(?:[\\S ]+)?(?:money|dollars|get|\\$))|i.want.(?:yo)?u(?:[\\S ]+)?li?(?:ek|ke)s?.this)|(?:this.is(?:.an?)?)?.(?:un)?hacked.comment|(?:pl(?:s|z|ease?).)?li?(?:ek|ke)s?(?:.this)?(?:.comment)?.so|gi(?:v|m+i?)e.m(?:ai|y).li?(?:ek|ke)s?|li?(?:ek|ke).my.comment)(?:(?!level|and|\\&).)*$", std::regex_constants::icase);

class $modify(CommentCell) {
	static void onModify(auto & self)
    {
        self.setHookPriority("CommentCell::loadFromComment", 900);
    }
	void loadFromComment(GJComment* p0) {
		auto comment = p0->m_commentString;
		if (Mod::get()->getSettingValue<bool>("enabled") && (std::regex_match(std::string(comment), likebaitComment)) && p0->m_userID != 16) {
			if (Mod::get()->getSettingValue<bool>("markAsSpam")) p0->m_isSpam = true;
			p0->m_likeCount = (p0->m_likeCount) * -10;
			p0->m_commentString = Mod::get()->getSettingValue<std::string>("replacementText");
		}
		CommentCell::loadFromComment(p0);
	}
};