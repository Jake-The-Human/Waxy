
from gi.repository import Adw
from gi.repository import Gtk

@Gtk.Template(resource_path='/org/waxy/Waxy/window.ui')
class WaxyWindow(Adw.ApplicationWindow):
    __gtype_name__ = 'WaxyWindow'

    label = Gtk.Template.Child()

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
