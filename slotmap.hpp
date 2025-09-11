    #pragma once
    #include <cstdint>
    #include <iostream>
    #include <vector>
    #include "aliases.hpp"
    

    struct Key {
        TypeInt idx_ {0};
        TypeInt gen_ {0};
    };

    struct ISlotmap {
        virtual ~ISlotmap() = default;
        virtual const void* dataAddress() const noexcept = 0;
        virtual TypeInt size() const noexcept = 0;
        virtual TypeInt sizeElement() const noexcept = 0;
    };

    template <typename TypeData>
    struct Slotmap : ISlotmap {

        explicit Slotmap (TypeInt capacity) : CAPACITY_(capacity) {

            indices_.resize(capacity);
            data_.resize(capacity);
            erase_.resize(capacity);
            initiateIndexes();
        };

        TypeInt constexpr capacity() const noexcept { return CAPACITY_; };

        const void* dataAddress() const noexcept {
            return data_.empty() ? nullptr
            : static_cast<const void*>(data_.data());
        }

        TypeInt sizeElement() const noexcept{
            return data_.empty() ? 0 : sizeof(TypeData);
        }

        TypeInt size() const noexcept {
            return data_.size();
        }
       
        void print() const noexcept {
            std::cout << "FREELIST: " << freelist_ << "\n";
            std::cout << "SIZE: " << size_ << "\n";
            std::cout << "INDICES:\t";
            for (auto& index : indices_) {
                std::cout << "ID:  " << index.idx_ << "\t";
            }
            std::cout << "\n\t\t";
            for (auto& index : indices_) {
                std::cout << "GEN: " << index.gen_ << "\t";
            }
            std::cout << "\n";
            std::cout << "DATA:\t\t";
            for (auto& data : data_) {
                std::cout << "DAT: " << data << "\t";
            }
            std::cout << "\n";
            std::cout << "ERASE:\t\t";
            for (auto& erase : erase_) {
                std::cout << "ERA: " << erase << "\t";
            }
            std::cout << "\n\n";
        }        

        Key push_back(TypeData&& data) {
            //Verificamos que hay sitio para insertar el dato
            if (size_ >= CAPACITY_) { throw std::runtime_error("No se puede insertar dato, capacidad llena"); }
            auto nowfreelist = freelist_;
            auto nextfreelist = indices_[freelist_].idx_;
            //Creamos la key que se va a devolver
            Key k;
            k.idx_ = nowfreelist;
            k.gen_ = indices_[nowfreelist].gen_;
            //Modificamos freelist_ que apunta al nuevo slot libre
            freelist_ = nextfreelist;
            //Modificar la key en el primer slot libre para que apunte a la posición del dato
            indices_[nowfreelist].idx_ = size_;
            //Insertamos el dato
            data_[size_] = std::move(data);
            //Asociamos la posición del Slot relacionado con el dato en erase_
            erase_[size_] = nowfreelist;
            //Modificamos la posición del siguiente hueco libre para datos
            ++size_;
            //Devolvemos la key al usuario
            return k;
        }

        Key push_back(TypeData const& data){
            return push_back(TypeData {data});
        }

        void remove(Key const& key) {
            Key& slot = indices_[key.idx_];
            auto id_slot_freed = slot.idx_;

            //Comprobar que las generaciones de la key y del slot son iguales
            if (key.gen_ != slot.gen_) { throw std::runtime_error("Generaciones diferentes al borrar"); }

            //Incremento de la generación del slot objetivo
            slot.gen_++;

            //Movemos el último dato y el dato asociado en erase_ al hueco libre
            data_[id_slot_freed]  = data_[size_-1];
            erase_[id_slot_freed] = erase_[size_-1];
            
            //Modificamos el slot al que apuntaba el dato más a la izquierda para que apunte en la nueva posición
            auto pos_slot_moved = erase_[id_slot_freed];
            indices_[pos_slot_moved].idx_ = id_slot_freed;

            //Cambiamos el slot que apuntaba el dato a liberar para que apunte al siguiente slot libre, y también que freelist_ apunte a este slot
            slot.idx_ = freelist_;
            freelist_ = key.idx_;

            //reducimos el tamaño de size
            --size_;
        }

        TypeData& getData (Key key) {
            if (key.gen_ != indices_[key.idx_].gen_)
                throw std::runtime_error("La key no apunta a un índice que contenga un dato");
            auto idx_data = indices_[key.idx_].idx_;
            return data_[idx_data];
        }

    private:        
        TypeInt freelist_ {0};
        TypeInt size_ {0};
        const TypeInt CAPACITY_;
        std::vector<Key> indices_ {};
        std::vector<TypeData> data_ {};
        std::vector<TypeInt> erase_ {};

        void initiateIndexes() noexcept {
            TypeInt i {0};
            for (auto& index : indices_) {
                index.idx_ = i++;
                index.gen_ = 0;
            }
        };
    };