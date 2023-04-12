#ifndef PLUGIN_INTERFACE_HPP
#define PLUGIN_INTERFACE_HPP

class Player;
class Entity;
class Block;
class Inventory;
class Chat;

class PluginInterface {
    public:
        PluginInterface();
        virtual ~PluginInterface();

    struct player {
        explicit player(PluginInterface *interface) : _intern(interface) {};

        // Checks
        bool isConnected() const;
        bool isBanned() const;
        bool hasAdvancement() const;
        bool hasRecipe() const;

        Player *getByID();
        Player *getByName();

        // Interaction
        void playSound();
        void kick();
        void ban();
        void giveAdvancement();
        void revokeAdvancement();
        void giveRecipe();
        void removeRecipe();

        private:
        PluginInterface *_intern;
    } player {this};

    struct entity {
        explicit entity(PluginInterface *interface) : _intern(interface) {};

        Entity *getByID();

        // Interactions
        void kill();
        void despawn();
        void heal();
        void damage();
        void teleport();
        void ride();
        void unride();
        void equip();
        void unequip();

        private:
        PluginInterface *_intern;
    } entity {this};

    struct block {
        explicit block(PluginInterface *interface) : _intern(interface) {};

        void getByID();
        void getByPosition();

        // Interactions
        void destroy();
        void place();

        private:
        PluginInterface *_intern;
    } block {this};

    struct inventory {
        explicit inventory(PluginInterface *interface) : _intern(interface) {};

        // Checks
        bool hasItem() const;

        Inventory *getByID()
        Inventory *getByPosition();

        // Interactions
        void addItem();
        void removeItem();
        void clear();

        private:
        PluginInterface *_intern;
    } inventory {this};

    struct chat {
        explicit chat(PluginInterface *interface) : _intern(interface) {};

        Chat *get();

        private:
        PluginInterface *_intern;
    } chat {this};

    struct command {
        explicit command(PluginInterface *interface) : _intern(interface) {};

        void registerCommand();
        void unregisterCommand();
        void raw();

        private:
        PluginInterface *_intern;
    } command {this};
};

#endif
