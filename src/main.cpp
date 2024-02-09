#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <regex>

using namespace geode::prelude;

const std::regex likebaitComment("(?:[\\S ]+)?(?:here.before|i.?.(?:[\\S ]+)?hack(?:ed)?.(?:this.?comment|my)|\\+1|(?:(?:\\d?.?)?like.?.?(?:.?\\d|if|si|=|d|button|this|for|to))|(?:can.i|if.this).?(?:gets?.)?(?:\\d|top)|claim.?your(?:[\\S ]+)?ticket|this.comment.is(?:.not)?.hack(?:ed)?|(?:enough|every.\\d(?:[\\S]+)?).likes?|(?:pl[sz]|get).(?:[\\S ]+)?\\d?likes?|this.comment.+likes?|like(?:[\\S ]+)? (?:or|and))(?:[\\S ]+)?", std::regex_constants::icase);

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