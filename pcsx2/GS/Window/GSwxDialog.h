/*  PCSX2 - PS2 Emulator for PCs
 *  Copyright (C) 2002-2021 PCSX2 Dev Team
 *
 *  PCSX2 is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  PCSX2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with PCSX2.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "GS.h"
#include "GSSetting.h"

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>
#include <wx/wrapsizer.h>
#include <wx/statline.h>
#include <wx/filepicker.h>
#include <vector>

class GSUIElementHolder
{
	class GSwxChoice : public wxChoice
	{
	public:
		const std::vector<GSSetting>& settings;

		GSwxChoice(
			wxWindow* parent,
			wxWindowID id,
			const wxPoint& pos,
			const wxSize& size,
			const wxArrayString& choices,
			const std::vector<GSSetting>* settings,
			long style = 0,
			const wxValidator& validator = wxDefaultValidator,
			const wxString& name = wxChoiceNameStr)
			: wxChoice(parent, id, pos, size, choices, style, validator, name)
			, settings(*settings)
		{
		}
	};

	struct UIElem
	{
		enum class Type
		{
			CheckBox,
			Choice,
			Spin,
			Slider,
			File,
			Directory,
		};

		Type type;
		wxControl* control;
		const char* config;
		wxCheckBox* prereq;

		UIElem(Type type, wxControl* control, const char* config, wxCheckBox* prereq)
			: type(type), control(control), config(config), prereq(prereq)
		{
		}
	};

	wxWindow* m_window;
	std::vector<UIElem> m_elems;

	void addWithLabel(wxControl* control, UIElem::Type type, wxSizer* sizer, const char* label, const char* config_name, int tooltip, wxCheckBox* prereq, wxSizerFlags flags = wxSizerFlags().Centre().Expand().Left());

public:
	GSUIElementHolder(wxWindow* window);
	wxCheckBox* addCheckBox(wxSizer* sizer, const char* label, const char* config_name, int tooltip = -1, wxCheckBox* prereq = nullptr);
	wxChoice* addComboBoxAndLabel(wxSizer* sizer, const char* label, const char* config_name, const std::vector<GSSetting>* settings, int tooltip = -1, wxCheckBox* prereq = nullptr);
	wxSpinCtrl* addSpin(wxSizer* sizer, const char* config_name, int min, int max, int initial, int tooltip = -1, wxCheckBox* prereq = nullptr);
	wxSpinCtrl* addSpinAndLabel(wxSizer* sizer, const char* label, const char* config_name, int min, int max, int initial, int tooltip = -1, wxCheckBox* prereq = nullptr);
	wxSlider* addSliderAndLabel(wxSizer* sizer, const char* label, const char* config_name, int min, int max, int initial, int tooltip = -1, wxCheckBox* prereq = nullptr);
	wxFilePickerCtrl* addFilePickerAndLabel(wxSizer* sizer, const char* label, const char* config_name, int tooltip = -1, wxCheckBox* prereq = nullptr);
	wxDirPickerCtrl* addDirPickerAndLabel(wxSizer* sizer, const char* label, const char* config_name, int tooltip = -1, wxCheckBox* prereq = nullptr);

	void Load();
	void Save();
	void Update();
};

namespace GSSettingsDialog
{

	class RendererTab : public wxPanel
	{
	public:
		GSUIElementHolder m_ui;

		RendererTab(wxWindow* parent);
		void Load() { m_ui.Load(); m_ui.Update(); }
		void Save() { m_ui.Save(); }
		void CallUpdate(wxCommandEvent& event);
	};

	class HacksTab : public wxPanel
	{
	public:
		GSUIElementHolder m_ui;
		wxSpinCtrl *skip_x_spin, *skip_y_spin;

		HacksTab(wxWindow* parent);
		void Load() { m_ui.Load(); Update(); }
		void Save() { m_ui.Save(); }
		void Update();
		void CallUpdate(wxCommandEvent& event);
	};

	class DebugTab : public wxPanel
	{
	public:
		GSUIElementHolder m_ui;
		wxSpinCtrl *start_dump_spin, *end_dump_spin;

		DebugTab(wxWindow* parent);
		void Load() { m_ui.Load(); Update(); }
		void Save() { m_ui.Save(); }
		void Update();
		void CallUpdate(wxCommandEvent& event);
	};

	class RecTab : public wxPanel
	{
	public:
		GSUIElementHolder m_ui;

		RecTab(wxWindow* parent);
		void Load() { m_ui.Load(); m_ui.Update(); }
		void Save() { m_ui.Save(); }
		void CallUpdate(wxCommandEvent& event);
	};

	class PostTab : public wxPanel
	{
	public:
		GSUIElementHolder m_ui;

		PostTab(wxWindow* parent);
		void Load() { m_ui.Load(); m_ui.Update(); }
		void Save() { m_ui.Save(); }
		void CallUpdate(wxCommandEvent& event);
	};

	class OSDTab : public wxPanel
	{
	public:
		GSUIElementHolder m_ui;

		OSDTab(wxWindow* parent);
		void Load() { m_ui.Load(); m_ui.Update(); }
		void Save() { m_ui.Save(); }
		void CallUpdate(wxCommandEvent& event);
	};

	class Dialog : public wxDialog
	{
		GSUIElementHolder m_ui;

		wxBoxSizer* m_top_box;
		wxChoice* m_adapter_select;
		RendererTab* m_renderer_panel;
		HacksTab* m_hacks_panel;
		DebugTab* m_debug_panel;
		RecTab* m_rec_panel;
		PostTab* m_post_panel;
		OSDTab* m_osd_panel;

	public:
		Dialog();
		~Dialog();
		void Load();
		void Save();
		void Update();
		void CallUpdate(wxCommandEvent& event);
	};

} // namespace GSSettingsDialog

extern bool RunwxDialog();