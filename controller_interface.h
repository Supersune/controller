namespace controller_interface
{
    class Controller
    {
    public:
        virtual bool init(hardware_interface *robotHW, ros::NodeHandle &nh);
        virtual void starting();
        virtual void update();
        virtual void stopping();
    };
}
