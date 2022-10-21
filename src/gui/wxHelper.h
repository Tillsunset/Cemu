#pragma once
#include <wx/string.h>
#include <wx/settings.h>

namespace wxHelper
{
	static wxColour primary = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
    // wxString to utf8 std::string
    inline std::string MakeUTF8(const wxString& str)
    {
        auto tmpUtf8 = str.ToUTF8();
        return std::string(tmpUtf8.data(), tmpUtf8.length());
    }

    inline fs::path MakeFSPath(const wxString& str)
    {
        auto tmpUtf8 = str.ToUTF8();
        auto sv = std::basic_string_view<char8_t>((const char8_t*)tmpUtf8.data(), tmpUtf8.length());
        return fs::path(sv);
    }

    inline wxString FromUtf8(std::string_view str)
    {
        return wxString::FromUTF8(str.data(), str.size());
    }

	inline wxColour getBackgroundPrimary() {
		return primary;
	}

	inline wxColour getBackgroundSecondary() {
		// get the background color so we can determine the theme in use
		wxColour bgColour = primary;
		uint32 bgLightness = (bgColour.GetRed() + bgColour.GetGreen() + bgColour.GetBlue()) / 3;
		bool isDarkTheme = bgLightness < 128;
		bgColour = bgColour.ChangeLightness(isDarkTheme ? 110 : 90);

		// for very light themes we'll use a blue tint to match the older Windows Cemu look
		if (bgLightness > 250)
			bgColour = wxColour(bgColour.Red() - 13, bgColour.Green() - 6, bgColour.Blue() - 2);

		return bgColour;
	}
};
